/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please checkout the README.md for more information
 */

#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]){
    if (argc < 3 or argc > 4){
        std::cout << "Error! Usage: winins path/to/iso path/to/device partition_size_for_parted\n";
        std::exit (3);
    }

    std::string partition_size = "100%";
    if (argc == 4){
        partition_size = argv[3];
    }

    if (not (std::filesystem::exists(argv[1]) and not std::filesystem::is_directory(argv[1]))){
        std::cout << "Error! The iso was not a valid file.\n";
        std::exit (3);
    }

    std::cout << "\033[92mMaking ntfs-file system on the device...\033[0m\n";
    std::system (std::string("sudo parted /dev/" + std::string(argv[2]) + " --script mklabel gpt mkpart primary ntfs 1MiB " + partition_size + " && sudo mkfs.ntfs -f /dev/" + std::string(argv[2]) + "1").c_str());

    std::cout << "\033[92mMaking win11 and iso directories at /mnt.\033[0m\n";
    std::system (std::string("sudo mkdir -p /mnt/win11\nsudo mkdir -p /mnt/iso").c_str());

    std::cout << "\033[92mMounting the iso and device to /mnt.\033[0m\n";
    std::system (std::string("sudo mount /dev/" + std::string(argv[2]) + "1 /mnt/win11").c_str());
    std::system (std::string("sudo mount -o loop " + std::string(argv[1]) + " /mnt/iso").c_str());

    std::cout << "\033[92mCopying iso to device.\033[0m\n";
    std::system ("sudo cp -r /mnt/iso/* /mnt/win11/");

    std::cout << "\033[92mSyncing the operations.\033[0m\n";
    std::system ("sudo sync");

    std::cout << "\033[92mMaking the device bootable.\033[0m\n";
    std::system (std::string("sudo winins-ms-sys -7 /dev/" + std::string(argv[2])).c_str());

    std::cout << "\033[92mUnmounting...\033[0m\n";
    std::system ("sudo umount /mnt/*");

    std::cout << "\033[92mcleaning the mnt.\033[0m\n";
    std::system ("sudo rm -rf /mnt/win11 /mnt/iso");

    std::cout << "\033[92mOperation was done.\033[0m\n";
}
