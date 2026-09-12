# Subject not verified

Investigation date: 2026-09-12. Repository baseline: `8bbe9fa` on `master`.

## Repository evidence checked

- Root tree, author file, Makefile, CMakeLists.txt, scene, source headers, and renderer implementation.
- All fetched remote branches: `Andrey`, `error`, `hgreenfe`, `kmeera-r`, `master`, `opencl`, `perlin`, `pthr`, `pthread`, and `rtv1`.
- Tags: none present.
- `git log --all --format= --name-only -- '*.pdf' '*subject*'`: only vendored SDL logo and zlib documentation PDF paths appeared; no assignment subject.

The `rtv1` binary/branch name and window title suggest historical naming, but do not prove an assignment or version. The source includes distance-based rendering, multiple complex shapes, textures, reflections, refraction, and unfinished OpenCL integration. Those features alone cannot distinguish an RT subject from an extended RTv1 implementation or a later continuation.

## Public-source check

Using BrowserOS neo, searched for `42 RT subject github pdf` and inspected the public [agavrel/42_Subjects index](https://github.com/agavrel/42_Subjects), which lists both RTv1 and RT.

- Direct GitHub repository search was secondary-rate-limited.
- The index's RT link led to [BenjaminSouchet/42_Subjects/00_Projects/03_Graphic/rt.pdf](https://github.com/BenjaminSouchet/42_Subjects/blob/master/00_Projects/03_Graphic/rt.pdf), which returned a Page not found view.
- No candidate PDF requirements were available from that link to compare against the source. Search snippets and project names were not treated as assignment evidence.

This bounded investigation did not establish an exact subject. It is not a claim that no matching PDF exists publicly.

## Evidence still needed

TODO: obtain the original assignment PDF from a confirmed contributor or official historical course record, including its project name and version/date. Compare mandatory primitives, lighting, scene input, platform requirements, and allowed/required bonuses against this source and its historical branches. Preserve uncertainty when code includes work beyond the original assignment.

Only after that check, store the untouched PDF at `docs/subject.pdf` and add `docs/subject-source.md` with source path/URL, retrieval date, SHA-256 checksum, matching evidence, and remaining uncertainty. No random subject PDF or checksum is supplied here.
