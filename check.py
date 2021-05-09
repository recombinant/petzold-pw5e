from pathlib import Path


def run():
    count = 0
    for p in Path().rglob("*.c"):
        if not str(p).startswith("Chapter"):
            continue

        data = p.read_text();
        # if "#include <windows.h" not in data:
        #     print(p)

        # data = p.read_text();
        # if "GetWindowLong(" in data:
        #     print(p)

        if "<tchar.h>" in data:
            assert "<windows.h>" in data
            idx1 = data.find("<tchar.h>")
            idx2 = data.find("<windows.h>")
            if idx1 < idx2:
                print(p, "=== tchar.h/windows.h")

        lines = data.splitlines(keepends=False)

        # if "_tWinMain" in data and "#include <tchar.h>" not in data:
        #     print("missing tchar.h:", p)
        #     if "#include <windowsx.h>" in data:
        #         for idx, line in enumerate(lines):
        #             if line == "#include <windowsx.h>":
        #                 lines.insert(idx, "#include <tchar.h>")
        #                 break
        #     else:
        #         for idx, line in enumerate(lines):
        #             if line == "#include <windows.h>":
        #                 lines.insert(idx, "#include <tchar.h>")
        #                 break

        if "_countof" in data and "stdlib.h" not in data:
            print(p, "=== missing <stdlib.h>")

        if '_tWinMain' in data and '\t_In_     int       nShowCmd)' not in data:
            print(p)

        if "_tWinMain" in data and "UNREFERENCED_PARAMETER(hPrevInstance);" not in data:
            print(p, "=== missing UNREFERENCED_PARAMETER(hPrevInstance);")
            assert data.count("hPrevInstance") == 1
            assert data.count("pCmdLine") <= 2, p
            assert data.count("nShowCmd") <= 2, p

        if "_tWinMain" in data and "UNREFERENCED_PARAMETER(hInstance);" in data:
             assert data.count("hInstance") - data.count(".hInstance") == 2, p

        if "_tWinMain" in data and "UNREFERENCED_PARAMETER(hPrevInstance);" in data:
            assert data.count("hPrevInstance") == 2, p

        if "_tWinMain" in data and "UNREFERENCED_PARAMETER(pCmdLine);" in data:
            assert data.count("pCmdLine") == 2, p

        if "_tWinMain" in data and "UNREFERENCED_PARAMETER(nCmdShow);" in data:
            assert data.count("nCmdShow") == 2, p



        count += 1

        # if "WinMain" not in data:
        #     print(p)

        #     for idx, line in enumerate(lines):
        #         if line == "#include <windows.h>":
        #             lines.insert(idx, "#define WIN32_LEAN_AND_MEAN")
        #             break

        # lines = [line.rstrip() for line in lines]
        # while not lines[-1]:
        #     lines = lines[:-1]
        # lines.append("")

        # p.write_text('\n'.join(lines));

    print(count)





if __name__ == "__main__":
	run()