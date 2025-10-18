from jinja2 import Environment, FileSystemLoader
from pathlib import Path
import sys

GENERATOR_FOLDER = Path(__file__).parent.resolve()
TEMPLATES_FOLDER = GENERATOR_FOLDER / "templates"
ROOT_FOLDER = GENERATOR_FOLDER.parent.parent.resolve()
CMAKELISTS_PATH = ROOT_FOLDER / "CMakeLists.txt"

environment = Environment(
    loader=FileSystemLoader(GENERATOR_FOLDER / "templates"))


def render_day_template(day_number: int, day_name: str):
    for template_path in (TEMPLATES_FOLDER).rglob("*.j2"):
        render = environment.get_template(str(template_path.relative_to(
            TEMPLATES_FOLDER))).render(day_number=day_number, day_name=day_name)
        relative_path = template_path.relative_to(TEMPLATES_FOLDER)
        output_path = ROOT_FOLDER / \
            f"day{day_number}" / \
            relative_path.with_suffix("")  # remove .j2 suffix
        output_path = Path(str(output_path).format(day_number=day_number))
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with open(output_path, "w") as f:
            f.write(render)


def add_day_to_cmakelists(day_number: int):
    # Using macro 'set(AOC_DAYS 1 2 3...)'
    with open(CMAKELISTS_PATH, "r") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if line.startswith("set(AOC_DAYS"):
            closing_parenthesis_index = line.index(")")
            new_line = line[:closing_parenthesis_index] + \
                f" {day_number}" + line[closing_parenthesis_index:]
            lines[i] = new_line
            break
    with open(CMAKELISTS_PATH, "w") as f:
        f.writelines(lines)


def main():
    if len(sys.argv) != 3:
        print("Usage: generate.py <day_number> <day_name>")
        sys.exit(1)
    day_number = int(sys.argv[1])
    day_name = sys.argv[2]
    render_day_template(day_number, day_name)
    add_day_to_cmakelists(day_number)


if __name__ == "__main__":
    main()
