import itertools
import pathlib

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

def main():
    pydir = pathlib.Path(__file__).parent.parent / "python"
    for fp in itertools.chain(pydir.rglob("*.cc"), pydir.rglob("*.i")):
        print(f"Processing {fp}")
        substitute_in_file(fp, "SWIG_Python_AppendOutput", "SWIG_AppendOutput")

if __name__ == '__main__':
    main()
