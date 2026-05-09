#!/usr/bin/env python3
"""Sanity-check every gen/data/*.lsp file.

Two checks per file:
  1. S-expression structure parses cleanly via sexpdata.
  2. All keyword symbols (tokens beginning with ':') are ASCII-only,
     so Cyrillic lookalikes such as :ру in place of :ru are caught.

Exits with code 1 on any failure, printing one error per offending file.
"""

from __future__ import annotations

import sys
from pathlib import Path

import sexpdata


REPO_ROOT = Path(__file__).resolve().parents[2]
DATA_DIR = REPO_ROOT / "gen" / "data"


def collect_symbols(node, out):
    if isinstance(node, sexpdata.Symbol):
        out.append(node)
    elif isinstance(node, list):
        for child in node:
            collect_symbols(child, out)


def check_file(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8")
    try:
        parsed = sexpdata.loads("(" + text + ")")
    except Exception as exc:
        return [f"{path.relative_to(REPO_ROOT)}: parse error: {exc}"]

    symbols: list[sexpdata.Symbol] = []
    collect_symbols(parsed, symbols)

    bad = []
    for sym in symbols:
        name = sym.value()
        if name.startswith(":") and not name.isascii():
            bad.append(name)

    if bad:
        unique = sorted(set(bad))
        return [
            f"{path.relative_to(REPO_ROOT)}: non-ASCII keyword(s): "
            + ", ".join(repr(k) for k in unique)
        ]
    return []


def main() -> int:
    files = sorted(DATA_DIR.glob("*.lsp"))
    if not files:
        print(f"No .lsp files found under {DATA_DIR}", file=sys.stderr)
        return 1

    errors: list[str] = []
    for path in files:
        errors.extend(check_file(path))

    if errors:
        for line in errors:
            print(line)
        print(f"\n{len(errors)} error(s) across {len(files)} file(s).")
        return 1

    print(f"All {len(files)} files passed.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
