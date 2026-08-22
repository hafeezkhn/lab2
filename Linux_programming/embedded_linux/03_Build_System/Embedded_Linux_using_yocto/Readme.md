## What is Yocto?

**Yocto** is the smallest SI metric system prefix.  

Like 'm' stands for milli (10^-3), **yocto** (symbol `y`) stands for 10^-24.  

---

## What is Yocto Project?

The **Yocto Project** provides open-source, high-quality infrastructure and tools to help developers create their own custom Linux distribution for any hardware architecture.

---

## History

The Yocto Project was **announced in 2010** and **formally launched in March 2011** to reduce work duplication and provide resources catering to both new and experienced users.  

It is a collaboration of:  
- Many hardware manufacturers  
- Open source operating system vendors  
- Electronics companies  

---

Yocto is also a **working group of the Linux Foundation**.  

To understand the outcome provided by Yocto Project, we can use the analogy of a computing machine:  

**Input:** Set of data describing what we want (Kernel Configuration, Hardware Name, Packages/Binaries to be installed)  

**Output:** Linux-based embedded product (Linux Kernel, Root File System, Bootloader, Device tree)  

---

## Setting Up Build Machine

### Prerequisites

1. 50 GBytes of free disk space  
2. Runs a supported Linux distribution (recent releases of Fedora, openSUSE, CentOS, Debian, or Ubuntu)  
3. Required versions:  
   - Git 1.8.3.1 or greater  
   - tar 1.27 or greater  
   - Python 3.4.0 or greater  

**Install required packages for Yocto:**  
https://www.yoctoproject.org/docs/latest/ref-manual/ref-manual.html#ubuntu-packages

```bash
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev \
pylint3 xterm
````

---

## Poky

**Poky** is the reference distribution of the Yocto Project. The word "reference" means "example" in this context.

Poky is used to build images (kernel, system, and application software) for targeted hardware.

Components included in Poky:

* **BitBake**
* **OpenEmbedded Core (OE-Core)**
* **meta-yocto-bsp**
* **Documentation**

**Note:** Poky does not contain binary files. It is a working example of how to build your own custom Linux distribution from source.

---

## Difference Between Poky and Yocto

* **Yocto**: Refers to the organization/project (like Canonical behind Ubuntu)
* **Poky**: Refers to the reference distribution you download (like Ubuntu OS itself)

---

## Metadata

**Non-Yocto:** Data describing other data

**Yocto World:** Metadata refers to build instructions and commands, specifying software versions and build procedures.

Metadata comes from patches or changes to software to fix bugs or customize builds.

**Metadata includes:**

* Configuration files (`.conf`)
* Recipes (`.bb`, `.bbappend`)
* Classes (`.bbclass`)
* Includes (`.inc`)

---

## OpenEmbedded Project

OpenEmbedded provides a cross-compile environment for creating complete Linux distributions for embedded systems.
Website: [http://www.openembedded.org/wiki/Main\_Page](http://www.openembedded.org/wiki/Main_Page)

---

## OpenEmbedded vs Yocto

* **OE-Core**: Core metadata shared between Yocto and OpenEmbedded
* **OpenEmbedded**: Not a reference distribution; foundation for multiple architectures and features
* **Yocto Project**: Provides tools, metadata, BSPs, and documentation for supported boards

---

## OpenEmbedded-Core (OE-Core)

Both projects share OE-Core, which includes recipes, classes, and associated files.

---

## BitBake

**BitBake** is a core build engine in Yocto Project.

* Similar in function to `make` but designed for complex dependencies
* Parses Python and shell scripts to generate and execute build tasks
* Handles fetching sources, building packages, and creating images
* Ensures reproducible builds and efficient use of processing resources

---

## meta-yocto-bsp

A **Board Support Package (BSP)** provides:

* Information about hardware features and kernel configuration
* Additional drivers and software components beyond generic Linux
* Hardware-specific support for development boards

**Supported BSPs in Poky:**

* Beaglebone (Texas Instruments)
* MPC8315E-RDB (Freescale)
* Generic x86/x86-64 PCs
* EdgeRouter Lite (Ubiquiti Networks)

**Note:** To develop on other hardware, additional Yocto layers may be required.

---

## Others

* **meta-poky**: Poky-specific metadata
* **Documentation**: Yocto Project manuals and source references

---

## Conclusion

Poky includes:

* OE-Core components
* BitBake build engine
* Demo BSPs
* Helper scripts to set up the build environment
* QEMU emulator for image testing

---
