# Components of a Modern Computer 

- One or more processors
- Main memory
- Disks
- Printer
- Keyboard
- Mouse
- Display
- Network interfaces *(hardware components that connect the computer or some other device to a computer network. Through this way, they enable the device to send/receive data over the network)*
- IO devices

```
---------------------------------------------------------------------------
(User Mode)  | Web Browser , E-Mail Reader , Music Player, ... | (Software)
---------------------------------------------------------------------------
(User Mode)  | User Interface Program                          | (Software) 
---------------------------------------------------------------------------
(Kernel Mode)| Operating System                                | (Software)
---------------------------------------------------------------------------
               Hardware                                        | (Hardware) 
---------------------------------------------------------------------------
```

Note that the although operating system is interacting with the hardware, it is **not a physical component of the hardware**. It is made up from **programs**, **code**, and **data** that are **used to manage the hardware and resources**. Therefore the operating system is seen as a **software**. Like any other software, it is written to follow some instructions and it is installed on a computer's storage device (e.g. hard drive).

If we want to define in another way, operating system **turns the ugly hardware** **into beautiful abstractions**. In other words, it **provides a user-friendly way to interact with the hardware** which is quite complex to deal with directly. 

Because the operating system manages the hardware resources, it can be seen as **resource manager** as well. 

Now let's take a look at the roles of the operating system from this perspective.

# Operating System as a Resource Manager

If we look from the top to the down **(top down view)** in this representation: 

```
---------------------------------------------------------------------------
(User Mode)  | Web Browser , E-Mail Reader , Music Player, ... | (Software)
---------------------------------------------------------------------------
(User Mode)  | User Interface Program                          | (Software) 
---------------------------------------------------------------------------
(Kernel Mode)| Operating System                                | (Software)
---------------------------------------------------------------------------
               Hardware                                        | (Hardware) 
---------------------------------------------------------------------------
```

the operating system **provides abstractions to application programs** (e.g. Music Player, Web Browser, etc.). Abstractions in here mean **simple representations of the hardware**. By providing these simple representations, it becomes more easy for the users and programmers to manage their tasks because they won't have to deal with the complexities of the hardware since these complexities and details will be hidden in these simple representations. 

If we look from the bottom to up **(bottom up view),** the operating system **manages the various components of the hardware**. Some of the tasks that are related to managing hardware might be CPU scheduling, allocating memory, etc.

And if we want to look from another perspective **(alternative view),** the goal of the operating systems is to **allocate the hardware resources in a structured, organized, and efficient manner**. 

# Two Main Tasks of Operating System

- One of the main tasks of the operating system is to **provide programmers a well-defined/organized/clean set of abstract resources.** These abstract resources can be used by the progammer to manipulate/interact with the hardware resources.

- Another main task of the operating system is to **manage the hardware resources.**

But how does the hardware look like ? Also what kind of resources the operating system manages and what kind of services it provides by using these resources ? Let's answer these questions one by one.

# Hardware 

CPU, main memory (RAM), storage devices (e.g., hard disk drives, solid state drives, etc.), IO devices (e.g., keyboards, mouse, etc.), GPU resources, network resources are some of the examples of the hardware components/resources that are managed by the operating system. 

And these **hardware resources/components are linked with each other through various communication channels**. An example of a communication channel is **bus** and it is basically a **collection of wires on a circuit board that carries signals and data between the these components**. Different components of the hardware can communicate with each other by using this bus. And the communication is done through various types of bus transactions. 

Bus transactions are operations that the hardware components use to exchange data. Some of the examples of the bus transactions are: 

- Load/store operations (When the CPU needs to read data from memory or when it needs to write data to memory, it initiates load or store transactions on the bus)
- Inter-process communication (Sending signal from one process to another on the bus) 
- Device accesses (When the CPU or other hardware component needs to communicate with devices such as storage devices, network interfaces, they initiatie device access transactions on the bus)
- ...

If we turn back to the hardware components that are managed by the operating system; what do we mean actually by managing these resources ? 

# Managing Resources 

## Allocation

We need to **allocate the resources to provide services**. And many of the resources such as 

- CPU
- Memory
- Disk
- Network

are very limited. So somebody has to decide which entity should get these resources at any given time for example. And this somebody is operating system.

## Protection

Protection of the resources when they are being used for an application is also very important concept in the operating system. **If an application is running and using the resources, another application should not interfere with that application.** 

## Reclamation 

The operating system provides the resources but if there are demands for these resources from other programs/application, then the operating system should be able to take these resources back and give them to the new program/application at some point. 

In addition, when the programs/application ends (either because of an error or they finished their executions), the resources should be reclaimed as well. **It is the operating system's responsibility to track the resources and reclaim once they are not being used anymore.**

## Virtualization

Virtualization is a method that allows the users to create the **virtual version** of resource(s). It **abstracts the real characteristics of the resource(s) and presents them in a new way that is easier, more efficient, and flexible to deal with**.

When we virtualize a physical resource, we hide the complexities and the details of this resource and create more simple view of this resource. This new virtualized resource can be seen as a layer between the physical resource and the application that access to that physical resource. After virtualizing a resource, the application will use this virtualized resource to access to the physical resource. 

We can create this layer in such a way that when the program needs more resources in time, the layer can allocate additional virtual resources to it by drawing resources from the available pool of physical resources. In that case, the virtual resources can be dynamically allocated and adjusted based on demand. That's why this results in the **illusion of infinite private resources**.

So we explained what do we mean when we say that operating system manages the resources but what are the services that the operating system provides by managing these resources ? 

# Operating System Services 

- Program development
Operating system **provides tools** such as **compilers, debuggers, IDEs** that are useful for **program development.**

- Program execution
It is also responsible from **executing programs** by **loading these programs into memory**, **allocating whatever resources they need**, and **starting their execution**.

- Access to IO devices
IO devices are **keyboards, mouse, printers**, etc. Operating system **manages the access to these devices**.

- Controlled access to files
**File creation, deletion, reading, writing are the services that are provided by the operating system to access to the data in storage devices**. And operating system implements control mechanisms to **ensure** that the **files are accessed by authorized users**.

- System access
Operating system also **controls access to the system resources and services**. It implements user authentication and provides user accounts, passwords, etc. to provide unauthorized access to the system resources. It also enables the users to make a request whenever they want to access to the services provided by the operating system (e.g., opening a file, reading data from a file, writing data to a file, etc.). This request is also called **system call** (e,g,. open(), read(), write(), etc.)

- Error detection and response
When the program is executed or in any other system operation, an error may occur. Operating system **provides error handling and exception mechanisms, takes corrective actions for these errors, and displays these errors to the users.**

- Accounting
**Recording the resource usage/consumption/utilization** is another service provided by the operating system.

In addition, we talked about what abstraction is previously. When the operating system presents the **storage devices** as **files and directories** in a hierarchical structure, for example, this can be given as an example of a **service** provided to the user. Because now the user can interact with the files and directories in a simple way without worrying about the complexities and details of how the data is stored physically in the storage devices in the hardware. 

In another example, the operating system can **present** the **physical memory addresses** as a **large space of virtual addresses**. In that case, each virtual address in this large space can point to a different address location in the physical memory. And the programs can use this large space of the virtual addresses to read/write the data in a specific address of the physical memory. This can be seen as a service as well. Representing the physical memory this way allows the programs to operate like they have access to a large memory space even though the memory is limited.

So these kinds of services brings **abstraction**, **simplification** and **convenience** for the users. Operating systems also ensures consistent and predictable environment for applications and users. This is the another service of the operating systems and it can be called as **standardization**.

At the end of the day, **operating system** is just a **program** that **runs with special privileges** to **implement allocation, protection, reclamation, virtualization**, and **the services that are structured on top of it**. 

If we want to look from a different perspective, operating system **provides a containers of resources**. And this should make the usage of the computer simpler.

Okay but what are the different types of operating systems ? And what are the different operating systems architectures ? 

# Operating Systems Types 

- Mainframe operating system
  - Designed for processor-intensive computing tasks
  - It is used by large organizations
  - They can handle massive amount of data processing, transaction processing, and batch processing
- Server operating system
  - Designed to run on servers
  - Provides services to other computers or devices over a network
- Multiprocessor operating system
  - Designed to manage the system with multiple processors
- Personal Computer (PC) operating system
- Embedded operating system
- Real-Time operating system
- Smart card operating system

# Different Architectures of Operating Systems

- Monolithic
- Layered systems
- Microkernels
- Client-server
- Virtual machines

So at the end, the operating system should provide **convenience** to users and programmers by creating an environment that is easy to deal with the underlying hardware of the computers/devices. It should provide **efficiency** to the users and progammers while ensuring efficient usage of the resources. Lastly, as the new technologies emerge in the hardware, operating system should be able to **evolve** and **adapt to these changes** in a flexible manner.

# Hardware and Software Infrastructure

```

-------------------------------------------------------------  
|     Application programs              |
|----------------------------------     |
|     Libraries/utilities         |     |       Software
|------------------------------   |     |
|     Operating system        |   |     |
|------------------------------------------------------------
|     Execution hardware                |
|                -----------------------|
|                |                      |
|-------------------------              |
|     Bus                |   Memory     |       Hardware 
|                        | translation* |    
|---------------------------------------|
| IO devices |        |      Main       |
|    and     |        |     memory      |
| networking |        |                 |
--------------        ---------------------------------------
```

**Memory translation is converting a virtual address into the corresponding physical memory address that the hardware can use to access the actual data in the main memory*

So operating system is manager, and the programs, applications, and processes are the customers. Hardware in this example is the one who provdes the resources. The operating system works in different environments and under different restrictions.

# CPU/Processor 

CPU is basically a chip that is made up from electronic components that are called transistors. Its primary job is to execute the instructions and perform operations on the data. 

Imagine that you ran a program in your computer. This program includes some set of instructions. And these instructions are sent to the CPU. Then CPU follows these instructions step by step to do the required tasks specified in the program. And while doing that, it can retrieve the data from the memory, manipulate that data according to the instructions, and then store the results back in the memory or maybe send them to monitor, or printer for instance. 

CPU generally has one or more cores. These **cores** are **physical processing units** that are **responsible from executing instructions** and performing computations in general. 

And we can divide the core into three groups: 

- Memory: In core, a **memory unit** is built to store & transfer information fastly/efficiently. This memory unit consists of **registers** and **cache**.
- Control Unit: These units **fetches** the **instructions** that are represented as bits from the memory unit, and **translates** those **instructions** into **electricity** or maybe light so that they can be **sent** to **other parts of the computer as signal**. 
- Arithmetic Logic Unit: This unit includes **electronic circuits**. And these circuits are responsible from **arithmetic and logic operations**. 

Each CPU has a specific set of instructions that are represented in binary form to follow. And this set of instructions is called **Instruction Set Architecture (ISA)**. 

In addition, CPUs contains a special storage locations within themselves to hold **data, instructions, memory addresses, etc.** **during the execution of a program**. They are very close to the execution units of the processors and that's why they can provide much faster access to the data when they are needed during the execution of a program compared to data in main memory or disk. 

We can group the registers under different categories: 

- General registers: These registers are used to **hold variables**, and **results that are obtained during the execution of the program temporarily.**
- Special registers
  - Program counter: This is one of the special registers that is **visible to the programmer**. It contains the **memory address of the next instruction**.
  - Stack pointer: Another special register is stack pointer. It **points to the top of the current stack** in memory. This is **visible to the programmer** as well.
  - Condition registers: These registers **store the outcome of arithmetic or logical operations** that are performed by the CPU. They contain **bits** that **represent the outcomes of the operations** (e.g., **whether the result of an operation is zero, positive, negative, too large**, etc.). These registers are **visible to the programmer.**
  - Program status word (PSW): These registers contain bits that indicate the operating mode of the CPU (e.g., kernel mode, user mode). Unlike the other 3 registers, they are **not visible to the programmer.**

# How Processors Work ? 

**CPU Cycles**: 

```
Fetch unit -> Decode unit -> Execute unit

```
```
Fetch unit -> Decode unit                         Execute Unit
                          \                     /
                           \____ Holding Buffer - Execute Unit   
                           /                    \ 
                          /                       Execute Unit
Fetch unit -> Decode unit


```

Pipeline: Fetch the instruction that will be executed after 2 steps (n+2) from the memory while decoding the instruction that will be executed in the next step (n+1) while executing the instruction in the current step (n). 

Here fetching means retrieving instruction from the memory. Decoding means interpreting the binary or machine code instruction to understand its meaning and how it should be executed. And executing means just executing the instruction. 

# Memory Storage Hierarchy 

```
       --------- 
       Registers
      ------------
         Cache
     ---------------
       Main memory
   -------------------
      Magnetic disk
  -----------------------
      Magnetic tape
----------------------------
```

- Registers are fasters accessible storage units within the CPU. They hold the data, instructions, and addresses that are immediately needed for execution. 
- Cache is another fast storage unit. It is located near the CPU. It acts like a temporary storage between the CPU and main memory. It stores frequently accessed data and instructions. It is faster to access to the data in cache compared to the main memory, magnetic disk, and magnetic tape but slower compared to the registers.
- Main memory is the primary storage location for data and instructions during the execution of a program. It holds the data of the currently running program.
- Magnetic disks are another storage units that have larger capacities compared to main memory, cache, and register. A disk can be considered as a device that consists of multiple sub-devices/components. These sub-devices may include disks, read-write head that is responsible from reading/writing data from/to the disk, etc. Each sub-device has a specific role in the overall functioning of the disk. The smallest physical unit of data storage is called **sector** in the disk. Each sector has a unique address and this address identifies the location of the unit of data storage on the disk. In addition disks have read/write heads. These heads move across the surface of the platters to access the data. To read or write data, these heads need to be positioned over the appropriate sector on the platter. The time that is required to move these heads to the desired location is an important factor in the performance of the disk. And the time it takes to move the head from the current location to the target location is called **seek time**. This is an important metric because through this way, we can measure the latency of data access. Lower seek time, for example, means faster access to the data. In addition, disks consume power during operations. That's why power maangement techniques (e.g., adjustment of the rotational speed based on the workload, the use of low-power modes in certain time frames, etc.) are used to reduce energy consumption and extend the life of the disk. Lastly, disks continue storing the data even when they are turned off unlike main memory.
- Magnetic tape has the largest capacities among all the options. It is often used for backup and archival purposes. Like in magnetic disks, the data are stored even if the magnetic tape is turned off.

# CPU Caches 

The motivation behind using caches is that if there is a data/instruction that was used during the execution of a program recently, that data/instruction will probably be used again in the near future. So why not we store them in temporary storage units that are close to the CPU so that we can access to the frequently used data/instructions faster ? 

When a program is executed, if an access to some data is required during the execution, CPU first checks the registers in itself to see if the data is in there. If not, it sends a request to cache controller. And cache controller checks if the data is already present in the cace. If CPU finds the data it is looking for in there, we call this **cache hit** and cache controller retrieves the data from the cache to the CPU. If the data is not found in the caches, we call this **cache miss** and in that case, cache controller sends a request to the main memory to fetch the required data from there. Then the main memory retrives data and give it to the cache controller so that it can store the copy of that data for the future use and then provides it to the CPU. 

Note that there are different levels of the caches such as L1, L2, L3, etc. L1 cache for example is the one that is closest to the CPU. As the level decreases, the distance of the cache from the CPU increases. And CPU basically searches for each one of these caches starting from L1 until the data is found. 

But when we use cache, we encounter some issues that need to be dealth with. For example, caches takes the data from the main memory and stores it temporarily. If there are multiple CPUs in a system, each of these CPU deals with its own cache. In that case, if multiple CPUs tries to access and modify the same shared data, this results in data inconsistency if the changes that are made by one CPU are not reflected in the caches of the other CPUs. So we need a mechanism to ensure that all CPUs can view the consistent view of the shared data. This is called **cache coherency**. 

# Operating System Major Components

- Process and Thread Management: Creating, implementing/scheduling, and terminating processes and threads. 
- Resource Management: Managing the resources. 
  - CPU
  - Memory
  - IO Device
- File System: Organization, storage, retrieval, and management of files and directories on storage devices.
- Bootstrapping (Booting): Starting up the operating system when the computer is turned on

# CPU Execution Modes 

Sometimes CPU uses different privileges and access rights during its operations. These different privileges and access rights can be called as execution modes as well. We can think of execution mode as some kind of like operating state. And each of these modes have different rules and capabilities. 

Two examples of the execution modes are kernel mode and user model. And the CPU switches between these modes based on the type of code that is being executed and the required privileges. 

**Kernel mode**, for example, is highly privileged mode. This means that when the CPU is running in kernel mode, it has unrestricted access to all system resources and can execute all available CPU instructions. 

The operating system kernel runs in kernel mode because it provides the core services in a protected way. 

**User mode**, on the other hand, can be seen as unprivileged or problem mode if we compare it with the kernel mode. It is a restricted execution mode. That's why when the CPU is running in user mode, it has limited access to the system resources and it can only execute a subset of CPU instructions. User mode excludes user from accessing critical resources. and applications/programs run in user mode for example. 

```
|---------------------------|------------------
|          Ring 3           | Least Privileged
|  -----------------------  |------------------
|  |       Ring 2        |  | 
|  |  |---------------|  |  |------------------
|  |  |    Ring 1     |  |  |
|  |  |   ---------   |  |  |------------------
|  |  |  | Ring 0 |   |  |  | 
|  |  |  |        |   |  |  | Most Privileged
|  |  |  | Kernel |   |  |  |
|  |  |  ----------   |  |  |------------------
|  |  |               |  |  |
|  |  |---------------|  |  |------------------
|  |                     |  |
|  |---------------------|  |------------------
|                           | Least Privileged
|---------------------------|------------------

      Protection Rings
```

But the applications/programs that are running in the user mode sometimes need to perform system related tasks such as reading from a file, writing to a file, etc. However, they cannot do this in the user mode because user mode does not provide the privileges to access the hardware resources. That's why in those cases, we should be able to switch from the user mode to the kernel mode. But how to do that ? 

# Exception / Trap / Interrupt 

There are mechanisms named exceptions, traps and interrupts that are built into CPU. These are represented by instructions, hardware signals or bit patterns in the CPU. And they are used to handle specific events/conditions. 

The handlings of exceptions, traps, and interrupts is performed by predefined routines/rules.

Exceptions, for example, are events that happens when CPU detects an unusual condition during the execution of the program. They occur automatically when CPU detects an error or an exceptional condition. Some of the examples of the exceptions are divison by zero, execution of an illegal instruction. Also exceptions are synchronous which means they occur as a direct result of the execution of specific instructions. 

But sometimes programs may need to request services or perform system related tasks. In those cases, a special kind of exception named **traps** are used. Traps are the mechanisms that are intentionally triggered by the user programs to request services from the operating system, perform system related tasks or access system resources that require the kernel level privileges. Requesting services from the operating system is done through another mechanism that provides an interface between the application and the operating system kernel. This mechanism is called **system call**. Systems calls are invoked with traps and as a result of that they transfer the control from user to the kernel. 

Some of the time frames when interrupts are used might be when a program allocates memory dynamically during the runtime with functions like malloc() or new(), when a program reads from or writes to a file, or when a new process is created with the existin process and fork() function. These kinds of functions (malloc(), new(), fork(), open(), read(), etc.) Like exceptions, they are synchronous which means they occur as a direct response to the execution of a specific instruction.

Aside from these, sometimes hardware devices such as keyboard, mouse may want to notify the CPU about a condition that requires immediate attention. Interrupts may happen when the user clicks a mouse, uses the keyboard, or the timer expires, etc.. By sending interrupts, we basically mean that the device needs attention. Unlike exceptions and traps, interrupts are asynchronous which means that their occurences are triggered by external events and independent from the program's execution. 

# CPU Execution Modes Switches 

User Mode -> Kernel Mode 
- Trap
- Interrupt
- Exception

Kernel Mode -> Kernel Mode 
- Interrupt
- Exception

Kernel Mode -> User Mode 
- Return from Interrupt (RFI)

```
  ---------------
  | Application |
  | ----------- |
  | Libraries   |
  | ----------- |
                        User Space 
------------------------------------
                       Kernel Space
  ---------------
  | Portable OS |
  |   Layer     |
  | ----------- |
  |   Machine   |
  |  dependent  |
  |    layer    |
  | ----------- |

```


# Note 

The electronic devices can represent two states depending on whether an electrical current occurs or not. The existence of electrical current is represented as 1 and the absence of electrical current is represented as 0. And this forms the basis of the binary number system. The value of the 0 or 1 is also called bit. With 1 bit, we can represent only 2^1 combinations: 0 or 1. With 2 bits, we can represent 2^2 = 4 combinations (00, 01, 10, 11). 

And by combining multiple bits, we can create larger units of data. Some of these large units of data have some specific names. 

For example, when we combine 

- **8 bits**, this 8 bits unit of data is called **bytes**. (2^3)

- **1024 bytes** this 1024 bytes unit of data is called **kilobytes**. (2^10*2^3 = 2^13)

- **1024 kilobytes**, this 1024 kilobytes unit of data is called **megabyte**. (2^10*2^13) = 2^23)

- **1024 megabytes**, this 1024 megabytes unit of data is called **gigabyte**. (2^10*2^23) = 2^33)

By using these data units, computers can represent and process a wide range of data (e.g. numbers, characters, instructions, etc.).








