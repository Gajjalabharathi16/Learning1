
# YOCTO PROJECT:

- Go to the Yocto Project website and navigate to the source repositories.

- Select Poky, then choose the scarthgap branch, and copy the repository link.

- Clone the repository using the following command:
  `git clone git://git.yoctoproject.org/poky`
- after cloning switch to latest version of scarthgap branch using `git checkout scarthgap`
  
![image](https://github.com/user-attachments/assets/2a82cb7d-6552-4ad0-bb81-6405e0fefecb)  

## <u>Environment setup and downloading poky reference</u> :
- Install visual studio and create workspace for our project
### Build host packages:
- You must install essential host packages on your build host. The following command installs the host packages based on an Ubuntu distribution:
- `sudo apt-get install build-essential chrpath cpio debianutils diffstat file gawk gcc git iputils-ping libacl1 liblz4-tool locales python3 python3-git python3-jinja2 python3-pexpect python3-pip python3-subunit socat texinfo unzip wget xz-utils zstd`
## Yocto project basic configuration and exploring the poky source
- The Yocto Project uses bitbake to process software packages and generate images.

- First, source the environment script to set up the build environment:
  
  `source oe-init-build-env`
  
- After sourcing you will be automatically entered into build directory.
  
  ### Build Folder:
  - In Build directory we have two important configuration files 1)bblayers.conf  2)local.conf
    # bblayers.conf:
    BBLAYERS ?= " ... "
  - Main variable: tells BitBake which layers to include in the build.
  - Each path points to a Yocto layer (a folder with recipes, classes, and configs).
  - You can add/remove layers here based on your project requirements.
    
    - ![Screenshot 2025-07-04 231121](https://github.com/user-attachments/assets/e58f95a4-c18d-48d8-aab6-80a3c9bb4806)
  # 2)local.conf:
  - This file is used to set machine type, image name, build parallelism, and other configuration settings specific to your       build.
   
- Let's take an example to do bitbake for an software package
  # Bitbake a software package(Drop bear):
- The Dropbear recipe is located in: `meta/recipe-core/dropbear`
- Run the command to build it: `bitbake dropbear`
- The following steps are executed internally from the recipe file (e.g., dropbear_2022.83.bb):  
     1)Fetch and downloads the source code .  
     2)Configures and compiles the source for the target architecture.   
     3)Install rootfs for our target board and perform some quality issues checks  




