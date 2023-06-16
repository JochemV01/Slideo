*Jochem Verstegen - 1561170 - FBP - Subject: AV Interaction*
# Design Brief
## Setting
There will be a transition period in which automated vehicles (AVs) will become more advanced and more common. A large part of this transition will consist of mixed traffic, which is a situation where humans manually driving a vehicle will share the roads with AVs. At first, AVs will not be fully automated yet, starting with level 3. But at some point, AVs can advance into fully automated vehicles capable of driving safely in any circumstances humans would be able to drive in. As AVs become increasingly more widespread, the opportunity to create an intelligent transport system (ITS) of sorts emerges, as this will lead to bigger advantages like increased safety, efficiency, sustainability and comfort (Ahangar et al., 2021).

This opportunity has already been identified by the EU, as is evident from their project called "[AutoNet2030](https://cordis.europa.eu/project/id/610542)", from 2013 to 2016. This project involved, amongst others, a definition of a network of AVs. As described by de La Fortelle et al. (2014): vehicles with a cooperative mode are either manually driven by a human while guided by the cooperation (*cooperative vehicle*), or support automated driving (*cooperative automated vehicle*). Cooperation should happen in local and global cooperative areas, where the local areas are meant for sharing manoeuvring information and the global areas are for communicating information like weather conditions or construction on a larger geographical area. Local cooperative areas can be either static or dynamic, the static area resides in infrastructure at strategic places like highway entrances or intersections, the dynamic area moves with a group of vehicles in short vicinity sharing similar traffic objectives. The goal of AutoNet is to allow cooperative vehicles to seamlessly create and join areas based on their positions relative to each other and infrastructure, it is a type of vehicle-to-everything (V2X) communication.

## Idea
My idea is to design a device, preferably physical with haptic interaction, which can be used on a bicycle. This device allows its user to become a part of the AutoNet network as described above, to understand it and interact in it. It can be used to actively participate in negotiations with other cooperative vehicles, mainly automated ones.

I will be focusing on a person driving a city bike, used as a means of personal transit from one location to another, on a route on which they are familiar. Using the device, the driver can indicate their plans, like what moves they are planning to make. The device will communicate this information with the network, in order to give the user feedback about whether its safe to make the move. This allows the user to take part in the complex communication within the system, and negotiate with it. A reason for aiming for haptic interaction is that it can be used with touch, decreasing the need to visually interact with the device. This way, the user does not have to shift their visual attention to the device and can continue monitoring their environment for safety. Additionally, it is a possibility to include multimodality in the design.

To have a clear goal for the design, it is important to determine a specific situation in which the design will be situated. This will be a major street with a speed limit of 50km/h, with a residential minor street on either side with a speed limit of 30km/h. The major street has painted bike lanes on either side, so cyclists are always on the right side of the street. The cyclist will be approaching these minor streets from the major street and wants to turn left into the left minor street. This would require crossing the street in order to complete the turn. The cyclist will use the device to indicate they are planning to make a left turn, using the feedback to determine if they can go or have to wait.

Some questions to be answered are:
- If the turn is not possible at the moment, how can this be made clear to the user?
- Is a system to communicate a human's intent desirable, or is it preferred to exclusively use eHMIs on other vehicles to tell the human where they can go?
	- Would people appreciate the extra control this gives them?
	- Would this change the amount of information to take into account when making a decision?
	- How would it affect trust levels?
- Would this only be helpful near the end of the transition period, or also earlier when AVs are not as common yet?
	- In case of a cooperative vehicle, which as described in AutoNet is not driving automatically, is communication more likely to happen through the network or from human to human?

Note that this device is not meant to replace eHMIs, but to coexist alongside it. Where eHMIs would be used to monitor the environment, this would be used to negotiate with the system.


## References
Ahangar, M. N., Ahmed, Q. Z., Khan, F. A., & Hafeez, M. (2021). A Survey of Autonomous Vehicles: Enabling Communication Technologies and Challenges. _Sensors_, _21_(3), Article 3. [https://doi.org/10.3390/s21030706](https://doi.org/10.3390/s21030706)

de La Fortelle, A., Qian, X., Diemer, S., Grégoire, J., Moutarde, F., Bonnabel, S., Marjovi, A., Martinoli, A., Llatser, I., Festag, A., & Sjöberg, K. (2014, September 8). _Network of automated vehicles: The AutoNet 2030 vision_. ITS World Congress. [https://hal-mines-paristech.archives-ouvertes.fr/hal-01063484](https://hal-mines-paristech.archives-ouvertes.fr/hal-01063484)
