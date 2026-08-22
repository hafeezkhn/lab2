# ARM Architecture Notes

<details>
  <summary><strong>ARMv7</strong></summary>

### Features
- 32-bit architecture
- Thumb-2 instruction set
- NEON SIMD support
- TrustZone security extensions

### Profiles
- ARMv7-A (Application)
- ARMv7-R (Real-time)
- ARMv7-M (Microcontroller)

</details>

<details>
  <summary><strong>ARMv8</strong></summary>

### Features
- AArch32 (32-bit) + AArch64 (64-bit) execution states
- Cryptography extensions (AES, SHA)
- Virtualization extensions
- Advanced SIMD (NEON) and floating-point improvements

### Profiles
- ARMv8-A (Application)
- ARMv8-R (Real-time, introduced later)
- ARMv8-M (Microcontroller)

</details>

<details>
  <summary><strong>ARMv9</strong></summary>

### Features
- Built on ARMv8 with enhanced security
- Confidential Compute Architecture (CCA)
- SVE2 (Scalable Vector Extension v2)
- Improved machine learning and DSP performance
- Memory tagging extension (MTE)

### Profiles
- ARMv9-A (Application, first rollout)

</details>

---


# ARM Architecture v8A-9A

<details>
  <summary><strong>ISA & Registers</strong></summary>

* A64 ISA (64-bit instruction set)
* Integer registers
* Instruction set:

  * Integer operations
  * Memory operations
  * Stack operations
  * System instructions (control registers, v7 compatibility)

</details>

<details>
  <summary><strong>Calling Conventions</strong></summary>

* AAPCS (Procedure Call Standard)
* Register usage for parameter passing
* Return values and stack usage

</details>

<details>
  <summary><strong>Memory System</strong></summary>

* Memory access (DRAM, device)
* Ordering model & barriers

  * `dmb`, `dsb`, `isb`
  * Load-acquire & store-release
* Semaphores & cache management

</details>

<details>
  <summary><strong>Floating Point, SIMD, Crypto</strong></summary>

* IEEE-754 floating-point compliance
* Advanced SIMD (NEON)
* Cryptographic extensions
* Registers & instructions

</details>

<details>
  <summary><strong>Exceptions & Interrupts</strong></summary>

* Four exception levels (EL0–EL3)
* Stack model, handler, thread
* Vector tables
* Syndrome registers
* Switching AArch32 / AArch64 state
* Return from exception

</details>

<details>
  <summary><strong>Paging & Virtual Memory</strong></summary>

* Memory management with page tables
* Granules: 4K, 16K, 64K
* Page sizes
* Features: Execute-never, pointer authentication, tagging
* TLB management

</details>

<details>
  <summary><strong>EL2 (Virtualization Support)</strong></summary>

* Processor features for virtualization
* Use of second-level page tables
* Memory partitioning
* I/O MMU (SMMU)
* UEFI execution during boot
* Secure EL2 (Confidential Compute)

</details>

<details>
  <summary><strong>TrustZone & Security</strong></summary>

* Secure World vs Normal World
* Secure Monitor (EL3)
* Trusted Execution Environment (TEE)
* Links to TrustZone in other architectures
* 32-bit and 64-bit TrustZone

</details>

<details>
  <summary><strong>Caches</strong></summary>

* Hardware cache coherency
* Cache responsibilities (L1/L2/L3)
* Cache control via software
* Integration with TrustZone

</details>

<details>
  <summary><strong>Power Management</strong></summary>

* Core power management & external controllers
* Power modes (domain-level shutdown)
* Instructions: WFI, WFE, SEV

</details>

<details>
  <summary><strong>Debug & RAS</strong></summary>

* Hardware & software debug features
* Performance monitoring unit (PMU)
* Reliability, Availability, Serviceability (RAS)

</details>

<details>
  <summary><strong>Boot Process & Firmware</strong></summary>

* Role of firmware in initialization
* Coherency & interconnect (ACE / CHI)
* GIC (Generic Interrupt Controller)
* Boot stages and EL transitions

</details>

---

* **ISA, Registers, Calling Conventions** → Instruction basics
* **Memory, Paging, Exceptions, ELs** → Execution model
* **TrustZone, Security, Caches, Power Mgmt, Debug** → System-level features
* **Boot Process & Firmware** → Platform integration

---
<p align="right">
  ➡️ <a href="Readme_aarch.md" style="color: #2e6c80;">Next: Armv8-A Fundamentals</a></br>
</p>
