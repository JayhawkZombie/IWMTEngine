from string import Template
from typing import List
import common
import reflection_utils

member_nvp_template_string = Template("ar(cereal::make_nvp(\"$varName\", val.$varName));")

serialize_function_template_string = Template("""
template<class Archive>
void serialize(Archive &ar, $type &val) {
    try {
        $nvps
    } catch (std::exception &e) {
        // Not sure what to do here
        std::cerr << "Archive error in $type: " << e.what() << std::endl;
    }
}
""")

def get_extra_includes():
    return [
        "#include <cereal/cereal.hpp>",
        "#include <cereal/archives/binary.hpp>",
        "#include <cereal/archives/json.hpp>",
        "#include <Serialization/SerializeTypes.h>"
    ]

def generate_serialization_functions(class_refl_data: List[reflection_utils.ReflectedClass]):
    """
    Generate serialization functions for all classes in `class_refl_data`.
    :param class_refl_data: List of reflected classes to serialize.
    :return: List of serialization functions as List[str]
    """

    """
    Generated functions should look like this:
    
    template<class Archive>
    void serialize(Archive &ar, Type &val) {
        ar(cereal::make_nvp(val, "valName"));
        ... repeat for each member
    }
    """

    all_serialization_functions = []
    for class_refl in class_refl_data:
        nvp_strings = []
        for member in class_refl.members:
            common.debug_log(f"Generating serialization function for member {member.var_name}")
            nvp_str = Template.safe_substitute(member_nvp_template_string, {
                "varName": member.var_name,
            })
            common.debug_log(f"Generated nvp string for ${member.var_name}: {nvp_str}")
            nvp_strings.append(nvp_str)

        class_serialize_function = Template.safe_substitute(serialize_function_template_string, {
            "type": class_refl.class_name,
            "nvps": "\n".join(nvp_strings),
        })
        all_serialization_functions.append(class_serialize_function)

    return all_serialization_functions
