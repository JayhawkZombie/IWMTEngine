import datetime
from datetime import datetime
import os

logMode = "low"

def set_log_mode(mode):
    global logMode
    logMode = mode

def debug_log(msg):
    if logMode == "verbose":
        msg_prefix = f"gen-refl"
        print(f"{msg_prefix}: {msg}")

def get_headers_to_parse(input_dir: str):
    debug_log(f"Searching for header files in {input_dir}")
    headers_to_parse = []
    for root, _, files in os.walk(input_dir):
        for filename in files:
            if filename.endswith(".h") or filename.endswith(".hpp"):
                header_path: str = str(os.path.join(root, filename))
                headers_to_parse.append(header_path)

    return headers_to_parse

def generate_file_includes(header_files, output_file):
    files = []
    for header_file in header_files:
        relpath = os.path.relpath(header_file)
        include_string = f'#include "{relpath}"'
        files.append(include_string)
    return f"""
    #include <Globals.h>
    #include <Logging/Logging.h>
{"\n".join(files)}
"""

def get_generated_file_comment(filename):
    now = datetime.now()
    name = os.path.basename(filename)
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    return f"""/**********************************
* {name}
* Generated at: {dt_string}
*/\n
"""
