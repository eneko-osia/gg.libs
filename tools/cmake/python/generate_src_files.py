#!/usr/bin/python3

from pathlib import Path
import pathlib

def get_files(directory: Path, recursive: bool = True, extensions: str = None, files: Path = None):
    if files is None:
        files = []
    if directory.is_dir():
        for it in directory.iterdir():
            if it.is_file():
                if extensions is None or it.suffix in extensions:
                    files.append(it)
            elif recursive:
                get_files(it, recursive, extensions, files)
    return files

def get_folders(directory: Path, recursive: bool = True, folders: Path = None):
    if folders is None:
        folders = []
    if directory.is_dir():
        for it in directory.iterdir():
            if not it.is_file():
                folders.append(it)
                if recursive:
                    get_folders(it, recursive, folders)
    return folders

def write_files_in_folder(fd, folder: str, directory: Path, extensions: str, whiteline: bool):
    files = get_files(directory.joinpath(folder), True, extensions)
    if len(files) > 0:
        if whiteline:
            fd.write("\n")
        fd.write("# %s files\n" % folder)
        fd.write("set(%s_files\n" % folder)
        for file in files:
            file_path = str(file.as_posix())
            file_path = file_path.replace(directory.as_posix(), "${CMAKE_CURRENT_SOURCE_DIR}")
            fd.write("    %s\n" % file_path)
        fd.write(")\n")
        return True
    return False

# open
current_path = pathlib.Path().cwd()
fd = open(current_path.joinpath("GGSrcFiles.cmake"),"w+")
fd.write("# @generated - run cmake configure to generate this file\n\n")

# write files
whiteline = False
whiteline = write_files_in_folder(fd, "deps",    current_path, [".h", ".hpp"],               whiteline)
whiteline = write_files_in_folder(fd, "include", current_path, [".h", ".hpp"],               whiteline)
whiteline = write_files_in_folder(fd, "src",     current_path, [".c", ".cpp"],               whiteline)
whiteline = write_files_in_folder(fd, "test",    current_path, [".h", ".hpp", ".c", ".cpp"], whiteline)

# groups
fd.write("\n")
fd.write("create_groups(${CMAKE_CURRENT_SOURCE_DIR} \"${deps_files}\")\n")
fd.write("create_groups(${CMAKE_CURRENT_SOURCE_DIR} \"${include_files}\")\n")
fd.write("create_groups(${CMAKE_CURRENT_SOURCE_DIR} \"${src_files}\")\n")
fd.write("create_groups(${CMAKE_CURRENT_SOURCE_DIR} \"${test_files}\")\n")

# close
fd.close()
