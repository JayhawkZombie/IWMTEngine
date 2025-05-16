import argparse
from datetime import datetime
from pathlib import Path
import json
import codegen.common as common
import os

start_time = datetime.now()

def set_nested_value(data, keys, value, type = str):
    """
    Sets a value in a nested dictionary given a list of keys.

    Args:
        data (dict): The dictionary to modify.
        keys (list): A list of keys representing the path to the value.
        value: The value to set.
        type (type): The type to use.
    """
    current = data
    for key in keys[:-1]:
        current = current.setdefault(key, {})
    current[keys[-1]] = type(value)


def remove_nested_value(data, keys):
    """
    Sets a value in a nested dictionary given a list of keys.

    Args:
        data (dict): The dictionary to modify.
        keys (list): A list of keys representing the path to the value.
        value: The value to set.
    """
    current = data
    for key in keys[:-1]:
        current = current.setdefault(key, {})
    del current[keys[-1]]



if __name__ == '__main__':
    start_time = datetime.now()
    parser = argparse.ArgumentParser(
        description='Patch JSON asset files'
    )
    parser.add_argument('--dir', required=True, help='Asset directory')
    parser.add_argument(
        '--ext', required=True,
        help='Extension of files to patch'
    )
    parser.add_argument(
        '--key', required=True,
        help='Key to patch in'
    )
    parser.add_argument(
        '--remove', required=False,
        default=False,
        help="Remove an entry from an asset"
    )
    parser.add_argument('--value', required=True, help='Value to patch')
    parser.add_argument(
        '-v', '--verbose',
        default=False,
        action='store_true',
        help='Verbose output'
    )
    args = parser.parse_args()
    if args.verbose:
        common.set_log_mode("verbose")
    common.debug_log("Patching JSON asset files")

    searchDir = args.dir
    fileExt = args.ext
    keyPath = args.key.split(',')
    common.debug_log("Key path: {}".format(keyPath))
    assetsToPatch = []
    common.debug_log("Remove ? {}".format(args.remove))
    isPatchAddition = args.remove is False
    common.debug_log("isPatchAddition: {}".format(isPatchAddition))



    for root, dirs, files in os.walk(searchDir):
        for file in filter(lambda f: Path(f).suffix == fileExt, files):
            assetsToPatch.append(os.path.join(root, file))

    common.debug_log("Patching {} assets: {}".format(len(assetsToPatch), assetsToPatch))

    for asset in assetsToPatch:
        common.debug_log("Processing asset: {}".format(asset))
        with open(asset, 'r') as f:
            data = json.load(f)
        if isPatchAddition:
            if args.value.startswith("\""):
                typeToUse = str
            else:
                typeToUse = int
            set_nested_value(data, keyPath, args.value, typeToUse)
        else:
            remove_nested_value(data, keyPath)
        with open(asset, 'w') as f:
            json.dump(data, f)
            common.debug_log("Wrote patched file: {}".format(asset))


