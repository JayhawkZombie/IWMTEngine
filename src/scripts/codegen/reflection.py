import os
import common
from datetime import datetime
from typing import List
import reflection_utils
from itertools import chain
from string import Template

meta_factory_name = "rFactory"

meta_template_string = Template("""using namespace entt::literals;
auto $metaFactoryName = entt::meta<$className>();
$metaFactoryName.ctor<>();""")

meta_data_template_string = Template('$metaFactoryName.data<&$className::$varName>("$description"_hs);')

def get_extra_includes():
    extra_includes: List[str] = []
    return extra_includes

def generate_reflection_function_for_class(class_reflection_info: reflection_utils.ReflectedClass):
    members_strings = []
    for member in class_reflection_info.members:
        code_string = Template.safe_substitute(meta_data_template_string, {
            "className": class_reflection_info.class_name,
            "varName": member.var_name,
            "description": member.description,
            "metaFactoryName": meta_factory_name,
        })
        escaped_code_string = code_string.replace('"', r'\"')
        s = f"""
            GlobalConsole->Debug("Registering {member.type_name} {member.var_name} {member.description}");
            GlobalConsole->Debug("\tCode string: {escaped_code_string}");
            {code_string}
        """
        members_strings.append(s)
    base_class_string = ""
    if class_reflection_info.base:
        base_class_string = f"{meta_factory_name}.base<{class_reflection_info.base}>();"
    meta_string = Template.safe_substitute(meta_template_string, {
        "metaFactoryName": meta_factory_name,
        "className": class_reflection_info.class_name,
    })
    return f"""
        void Reflect_{class_reflection_info.class_name.replace(":", "_")}() {{
            std::cerr << "\tRegistering class {class_reflection_info.class_name}" << std::endl;
            {meta_string}
            {base_class_string}
            {"\n\t".join(members_strings)}
        }}
    """


def generate_register_all_call(all_classes_refl: List[reflection_utils.ReflectedClass]):
    ftn_calls = []
    for cls in all_classes_refl:
        ftn_call_string = f'Reflect_{cls.class_name.replace(":", "_")}();'
        ftn_calls.append(ftn_call_string)
    return f"""
        void Reflect_RegisterAll() {{
            std::cerr << "Registering all reflection classes" << std::endl;
            {"\n\t".join(ftn_calls)}
        }}
    """

def generate_reflection_code(all_classes_refl: List[reflection_utils.ReflectedClass]):
    """
    :param all_classes_refl: List of ReflectedClass objects
    :return: Generated functions for registering all reflection functions
    """

    all_class_refl_info = []

    # We only want to include headers thst actually
    # reflect a class
    # And we don't want to include internal headers
    # or unrelated headers (like imgui, etc)
    # headers_to_include = []

    # for header_path in all_headers_to_parse:
    #     class_reflection_info = reflection_utils.parse_reflection_macros(header_path)
    #     if len(class_reflection_info) == 0:
    #         common.debug_log(f"No markers in {header_path}, skipping...")
    #         continue
    #     headers_to_include.append(header_path)
    #     all_class_refl_info.extend(class_reflection_info)
    #     for cls in class_reflection_info:
    #         common.debug_log(f"Generating reflection code for class {cls}")
    #         fn = generate_reflection_function_for_class(cls)
    #         generated_code_strings.append(fn)
    #         common.debug_log(f"Done generating reflection code for class {cls.class_name}")
            # for members in cls.members
        # for cls in class_reflection_info
    # for header_path in headers_to_parse

    # all_class_refl_info, headers_to_include = gather_reflection_data(all_headers_to_parse)

    generated_code_strings = []
    for cls_refl_info in all_classes_refl:
        common.debug_log(f"Generating reflection function for {cls_refl_info.class_name}...")
        generated_code_strings.append(generate_reflection_function_for_class(cls_refl_info))
        common.debug_log(f"Done generating reflection function for {cls_refl_info.class_name}...")

    return generated_code_strings
