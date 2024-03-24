# Components of a Modern Computer 

- One or more processors
- Main memory
- Disks
- Printer
- Keyboard
- Mouse
- Display
- Network interfaces *(hardware components that connect the computer or some other device to a computer network. They enable the device to send/receive data over the network)*
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

Note that the although Operating System is interacting with the hardware, it is not a physical component of the hardware. It is made up from programs, code, and data that are used to manage the hardware and resources. Therefore the operating system is seen as a **software**. Like any other software, it is written to follow some instructions and it is installed on a computer's storage device (e.g. hard drive).

If we want to define in another way, the operating system turns the ugly hardware into beautiful abstractions. In other words, it provides a user-friendly way to interact with the hardware which is quite complex to deal with directly. 

Now let's take a look at the roles of the operating system in more detail.

# Operating System as a Resource Manager

Because the operating system manage the hardware resources, it can be seen as resource manager as well. 

If we look from the top to the down (top down view) in this representation: 

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

the operating system provides abstractions to application programs (e.g. Music Player, Web Browser, etc.). Abstractions in here are more simple representations of the hardware. By providing these abstractions, it becomes more easy for the user to manage his tasks. 

If we look from the bottom to up (bottom up view), the operating system manages the various components of the hardware. Some of the tasks that are related to managing hardware might be CPU scheduling, allocating memory, etc.

And if we want to look from another perspective (alternative view), the goal of the operating systems allocates the hardware resource in a structured, organized, and efficient manner. 

Okay now it is time to emphasize the main responsibilities/tasks of the operating system after giving all these knowledge.

# Two Main Tasks of Operating System

- One of the main tasks of the operating system is to provide programmers a well-defined/organized/clean set of abstract resources. These abstract resources can be used by the progammer to manipulate/interact with the hardware resources.

- Another main task of the operating system is to manage the hardware resources.

But now the question is how does the hardware look like ? Also what kind of resources the operating system manages and what kind of services it provides by using these resources ? Let's answer these questions one by one.

# Hardware 

The hardware resources/components are linked with each other through a data channel. This data channel is called bus and it is basically a collection of wires on a circuit board that carries signals and data between the these components. Different components of the hardware can communicate with each other by using this bus. And the communication is done through various types of bus transactions. 

Bus transactions are operations that the hardware components use to exchange data. Some of the examples of the bus transactions are: 

- Load/store operations (When the CPU needs to read data from memory or when it needs to write data to memory, it initiates load or store transactions on the bus)
- Inter-process communication (Sending signal from one process to another on the bus) 
- Device accesses (When the CPU or other hardware component needs to communicate with devices such as storage devices, network interfaces, they initiatie device access transactions on the bus)
- ...

# Resources 

## Allocation

We need to allocate the resources to provide services. And many of the resources such as 

- CPU
- Memory
- Disk
- Network

are very limited. So somebody has to decide which entity should get these resources at any given time for example.

## Protection

Protection of the resources when they are being used for an application is also very important concept in the operating system. If an application is running and using the resources, another application should not interfere with that application. 

## Reclamation 

The operating system provides the resources but if there are demands for these resources from other programs/application, then the operating system has to be able to take these resources back and give them to the new program/application at some point. 

In addition, when the programs/application ends (either because of an error or they finished their executions), the resources should be reclaimed as well. It is the operating system's responsibility to track the resources and reclaim once they are not being used. 

## Virtualization

Virtualization is a method that allows the users to create the **virtual version** of resource(s). It abstracts the real characteristics of the resource(s) and presents them in a new way that is easier, more efficient, and flexible to deal with.

When we virtualize a physical resource, we hide the complexities and the details of this resource and create more simple view of this resource. This new virtualized resource can be seen as a layer between the physical resource and the application that will use that physical resource. After virtualizing a resource, the application will use this virtualized resource to access to the physical resource. 

And we can create this layer in such a way that when the program needs more resources, the layer can allocate additional virtual resources to it by drawing resources from the available pool of physical resources. In other words, the virtual resources can be dynamically allocated and adjusted based on demand. That's why this results in the **illusion of infinite private resources**.

# Services 

When the operating system presents the storage devices as files and directories in a hierarchical structure, this can be given as an example of abstraction. Because now the user can interact with the files and directories in a simple way without worrying about the complexities and details of how the data is stored physically in the storage devices in the hardware. 

In another example, the operating system can present the physical memory as a large space of virtual addresses. In that case, each virtual address in that space can point to a different address location in the physical memory. And the programs can use this space of the virtual addresses to read the data in a specific address of the physical memory. Representing the physical memory this way allows the programs to operate like they have access to a large memory space even though the memory is limited.

So these kinds of services brings abstraction, simplification and convenience for the users. Operating systems also ensures consistent and predictable environment for applications and users. This is the another service of the operating systems and it can be called as standardization.

At the end of the day, operating system is just a program that runs with special privileges to implement allocation, protection, reclamation, virtualization, and the services that are structured on top of it. 

If we want to look from a different perspective, operating system provides a containers of resources. And this should make the usage of the computer simpler.

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

# Note 

The electronic devices can represent two states depending on whether an electrical current occurs or not. The existence of electrical current is represented as 1 and the absence of electrical current is represented as 0. And this forms the basis of the binary number system. The value of the 0 or 1 is also called bit. With 1 bit, we can represent only 2^1 combinations: 0 or 1. With 2 bits, we can represent 2^2 = 4 combinations (00, 01, 10, 11). 

And by combining multiple bits, we can create larger units of data. Some of these large units of data have some specific names. 

For example, when we combine 

- **8 bits**, this 8 bits unit of data is called **bytes**. (2^3)

- **1024 bytes** this 1024 bytes unit of data is called **kilobytes**. (2^10*2^3 = 2^13)

- **1024 kilobytes**, this 1024 kilobytes unit of data is called **megabyte**. (2^10*2^13) = 2^23)

- **1024 megabytes**, this 1024 megabytes unit of data is called **gigabyte**. (2^10*2^23) = 2^33)

By using these data units, computers can represent and process a wide range of data (e.g. numbers, characters, instructions, etc.).








