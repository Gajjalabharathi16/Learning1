
# YOCTO PROJECT:

- Go to yocto project website and serach for source repository,select poky,select scarthgap and copy the link of repository.
  `git clone git://git.yoctoproject.org/poky`
- after cloning switch to latest version of scarthgap branch using `git checkout scarthgap`
  
![image](https://github.com/user-attachments/assets/2a82cb7d-6552-4ad0-bb81-6405e0fefecb)  

## <u>Environment setup and downloading poky reference</u> :
- Install visual studio and create workspace for our project
### Build host packages:
- You must install essential host packages on your build host. The following command installs the host packages based on an Ubuntu distribution:
- `sudo apt-get install build-essential chrpath cpio debianutils diffstat file gawk gcc git iputils-ping libacl1 liblz4-tool locales python3 python3-git python3-jinja2 python3-pexpect python3-pip python3-subunit socat texinfo unzip wget xz-utils zstd`
## Yocto project basic configuration and examining poky source
- In yocto process we will be using bitbake commands in order to process any software package or image through the build        system.
- Before that we need to source the environment script.Go to poky and source the script using `source oe-init-build-env`
- After sourcing ,we will notice that we automatically entered into build folder
  ### Build Folder:
  - here we have two important file 1)bblayers.conf  2)local.conf
    # bblayers.conf:
    BBLAYERS ?= " ... "
  - Main variable: tells BitBake which layers to include in the build.
  - Each path points to a Yocto layer (a folder with recipes, classes, and configs).
  - You can add/remove layers here based on your project needs.
    
    - ![Screenshot 2025-07-04 231121](https://github.com/user-attachments/assets/e58f95a4-c18d-48d8-aab6-80a3c9bb4806)
   
- Let's take an example to do bitbake for an software package
- Now take dropbear package which is locaed in layer `meta/recipe-core/dropbear`
- perform `bitbake dropbear`
- All the tasks that are parsed from this dropbear_2022.83.bb recipe recipe will be built
  1)First this tasks will fetch and download the source code
  2)Do the configuration and compilation
  3)Install rootfs and perform some quality issues checks





