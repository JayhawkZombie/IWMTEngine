from typing import List
import re
import common

class ReflectedMember:
    def __init__(self, type_name: str, var_name: str, description: str):
        self.type_name = type_name
        self.var_name = var_name
        self.description = description

    def __repr__(self):
        return f"{self.type_name} {self.var_name} ({self.description})"


class ReflectedClass:
    def __init__(self, class_name: str):
        self.class_name = class_name
        self.members: List[ReflectedMember] = []
        self.base: str = ""

    def add_member(self, member: ReflectedMember):
        self.members.append(member)

    def __repr__(self):
        members_repr = "\n  ".join(str(member) for member in self.members)
        class_string = f"class {self.class_name}"
        if self.base:
            class_string = f"{class_string} < {self.base}"
        return f"Class: {class_string}\n  {members_repr}"


def parse_old_style_macros(file_path: str) -> List[ReflectedClass]:
    class_begin_pattern = re.compile(r'RENGINE_REFLECT_CLASS_BEGIN\(([\w:]+)\)')
    class_end_pattern = re.compile(r'RENGINE_REFLECT_CLASS_END\(([\w:]+)\)')
    member_pattern = re.compile(r'RENGINE_REFLECT_CLASS_MEMBER\(([\w:<>]+),\s*(\w+),\s*"([^"]+)"\)')
    base_class_pattern = re.compile(r'RENGINE_REFLECT_BASE_CLASS\((\w+)\)')

    classes = []
    current_class = None

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()

            # Match class start
            match = class_begin_pattern.match(line)
            if match:
                current_class = ReflectedClass(match.group(1))
                continue

            # Match class end
            match = class_end_pattern.match(line)
            if match and current_class:
                if current_class.class_name == match.group(1):
                    classes.append(current_class)
                    current_class = None
                continue

            # Match class members
            if current_class:
                match = member_pattern.match(line)
                if match:
                    type_name = match.group(1)
                    var_name = match.group(2)
                    description = match.group(3)
                    current_class.add_member(ReflectedMember(type_name, var_name, description))
            # Match base classes
            if current_class:
                match = base_class_pattern.match(line)
                if match:
                    current_class.base = match.group(1)

    return classes

def parse_new_style_macros(file_path: str) -> List[ReflectedClass]:
    reflectable_begin_pattern = re.compile(r'RENGINE_REFLECTABLE_BEGIN\(([\w:]+)\)')
    reflectable_end_pattern = re.compile(r'RENGINE_REFLECTABLE_END\(([\w:]+)\)')
    property_pattern = re.compile(r'RENGINE_REFLECT_PROPERTY\((\w+)\)')

    classes = []
    current_class = None
    in_class_definition = False

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()

            # Match class start
            match = reflectable_begin_pattern.match(line)
            if match:
                common.debug_log(f"Matched new class pattern {match.group(1)}")
                current_class = ReflectedClass(match.group(1))
                in_class_definition = True
                continue

            # Match class end
            match = reflectable_end_pattern.match(line)
            if match and current_class and in_class_definition:
                if current_class.class_name == match.group(1):
                    common.debug_log(f"End of new class pattern {match.group(1)}")
                    classes.append(current_class)
                    current_class = None
                    in_class_definition = False
                continue

            # Match property
            if current_class and in_class_definition:
                match = property_pattern.match(line)
                if match:
                    var_name = match.group(1)
                    common.debug_log(f"Matched new var pattern {var_name}")
                    # For new style, we use the variable name as both type and description
                    current_class.add_member(ReflectedMember(var_name, var_name, var_name))
                    continue
    common.debug_log(f"Classes {classes}")
    return classes

def parse_reflection_macros(file_path: str) -> List[ReflectedClass]:
    """
    Parse both old and new style reflection macros from a file.
    Returns a list of ReflectedClass objects containing all reflected classes.
    """
    # Parse both styles and combine results
    old_style_classes = parse_old_style_macros(file_path)
    new_style_classes = parse_new_style_macros(file_path)
    
    # Combine results, ensuring no duplicate class names
    all_classes = old_style_classes.copy()
    for new_class in new_style_classes:
        # Check if we already have this class from old style
        if not any(c.class_name == new_class.class_name for c in all_classes):
            all_classes.append(new_class)
    
    return all_classes

def gather_reflection_data(input_files: List[str]):
    """
    :param input_files: List of files to search for reflection data in
    :return: list of ReflectedClass objects, and the headers to include to
             access all of those classes
    """
    all_class_refl_info = []
    headers_to_include = []

    for header_path in input_files:
        class_reflection_info = parse_reflection_macros(header_path)
        if len(class_reflection_info) == 0:
            common.debug_log(f"No markers in {header_path}, skipping...")
            continue
        headers_to_include.append(header_path)
        all_class_refl_info.extend(class_reflection_info)

    return all_class_refl_info, headers_to_include
