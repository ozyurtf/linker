# Components of a Modern Computer 

- One or more processors
- Main memory
- Disks
- Printer
- Keyboard
- Mouse
- Display
- Network interfaces
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

- 






