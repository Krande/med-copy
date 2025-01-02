import itertools
import pathlib
import re

def substitute_in_file(file_path: pathlib.Path, old: str, new: str):
    """
    Replaces all occurrences of `old` with `new` in the given file.
    """
    with file_path.open("r", encoding="utf-8") as file:
        content = file.read()
    updated_content = content.replace(old, new)
    if content != updated_content:
        with file_path.open("w", encoding="utf-8") as file:
            file.write(updated_content)
        print(f"Updated {file_path}")

def add_value_arg_to_swig_function(file_path: pathlib.Path, function_name: str, value: str):
    """
    Adds an extra parameter `value` to the specified function in the given file.
    """
    with file_path.open("r", encoding="utf-8") as file:
        content = file.read()

    # Regex pattern to find the function calls and add the value argument
    pattern = rf"({function_name}\s*\([^)]*)\)"
    replacement = rf"\1, {value})"

    updated_content = re.sub(pattern, replacement, content)

    if content != updated_content:
        with file_path.open("w", encoding="utf-8") as file:
            file.write(updated_content)
        print(f"Added '{value}' argument to {function_name} in {file_path}")

def main(add_arg=False):
    pydir = pathlib.Path(__file__).parent.parent / "python"
    for fp in itertools.chain(pydir.rglob("*.cc"), pydir.rglob("*.i")):
        print(f"Processing {fp}")
        if add_arg:
            add_value_arg_to_swig_function(fp, "SWIG_Python_AppendOutput", value="0")
        else:
            substitute_in_file(fp, "SWIG_Python_AppendOutput", "SWIG_AppendOutput")

if __name__ == '__main__':
    main(add_arg=True)  # Set add_arg=True to add the `value` argument, False to replace the function name
