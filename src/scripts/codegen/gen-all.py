import argparse
import sys
from datetime import datetime
from itertools import chain
import reflection_utils

import common
import reflection
import serialization

start_time = datetime.now()

if __name__ == '__main__':
    start_time = datetime.now()
    parser = argparse.ArgumentParser(
        description='Generate reflection files from input directory'
    )
    parser.add_argument(
        '--input', required=True,
        help='Directory with input files'
    )
    parser.add_argument(
        '--output', required=True,
        help='Directory with output files'
    )
    parser.add_argument(
        '-v', '--verbose',
        default=False,
        action='store_true',
        help='Verbose output'
    )
    args = parser.parse_args()
    common.debug_log("Generating reflection data")

    if args.verbose:
        common.set_log_mode("verbose")

    input_dir = args.input if args.input else ""
    outputs = args.output if args.output else ""


    # could be multiple include dirs, so split by comma?
    all_input_dirs = input_dir.split(",")
    all_output_files = outputs.split(",")
    common.debug_log(f"Looking in {",".join(all_input_dirs)}")
    common.debug_log(f"Outputting to {",".join(all_output_files)}")

    if len(all_output_files) != 2:
        print("Please provide exactly two output files")
        sys.exit(1)

    nested_all_headers_to_parse = list(map(common.get_headers_to_parse, all_input_dirs))
    all_headers_to_parse = list(chain.from_iterable(nested_all_headers_to_parse))

    common.debug_log(f"{all_input_dirs} -> {",".join(all_output_files)}")
    common.debug_log(f"Found {len(all_headers_to_parse)} header files to parse")

    all_class_refl_info, headers_to_include = reflection_utils.gather_reflection_data(all_headers_to_parse)
    common.debug_log(f"Gathered reflection data on {len(all_class_refl_info)} classes")

    # First output file is for reflection
    refl_output_file = all_output_files[0]
    common.debug_log(f"Writing reflection code to {refl_output_file}")

    refl_file_comment = common.get_generated_file_comment(refl_output_file)
    refl_file_includes = common.generate_file_includes(headers_to_include, refl_output_file)
    refl_file_includes += "\n".join(reflection.get_extra_includes())
    all_class_reflection_functions = reflection.generate_reflection_code(all_class_refl_info)
    register_all_call = reflection.generate_register_all_call(all_class_refl_info)

    common.debug_log(f"Generated {len(all_class_reflection_functions)} reflection functions")
    common.debug_log(f"Writing reflection file {refl_output_file}")
    with open(refl_output_file, "w") as f:
        f.write(refl_file_comment.strip(" \t"))
        f.write(refl_file_includes)
        f.write(f"""\n{"\n".join(all_class_reflection_functions)}""")
        f.write(f"""\n{register_all_call}""")
    common.debug_log(f"Done writing reflection file {refl_output_file}")

    # Second output file is for serialization
    serial_output_file = all_output_files[1]
    common.debug_log(f"Writing serialization code to {serial_output_file}")

    serial_file_comment = common.get_generated_file_comment(serial_output_file)
    serial_file_includes = common.generate_file_includes(headers_to_include, serial_output_file)
    serial_file_includes += "\n".join(serialization.get_extra_includes())
    all_class_serialize_functions = serialization.generate_serialization_functions(all_class_refl_info)

    common.debug_log(f"Generated {len(all_class_serialize_functions)} serialization functions")

    common.debug_log(f"Writing serialization file {serial_output_file}")
    with open(serial_output_file, "w") as f:
        f.write("#pragma once\n")
        f.write(serial_file_comment.strip(" \t"))
        f.write(serial_file_includes)
        f.write(f"""\nnamespace cereal {{\n{"\n".join(all_class_serialize_functions)}\n}}//namespace cereal\n""")
    common.debug_log(f"Done writing serialization file {serial_output_file}")
