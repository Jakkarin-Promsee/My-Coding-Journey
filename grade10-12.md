# [<-- Back to all journey page -->](README.md)

# My Project Between Grade 10-12 (Oldest - Lastest)
- [**Water Quality Monitoring and Notification Machine for Increase Efficiency of Water Treatment using Artificial Intelligence (JAPS.)**](#water-quality-monitoring-and-notification-machine-for-increase-efficiency-of-water-treatment-using-artificial-intelligence-japs)
- [**Era Odyssey, The IDLE Game to provide knowledge about geological time (Moblie)**](#era-odyssey-the-idle-game-to-provide-knowledge-about-geological-time-moblie)

<!-- # My Other Project -->

---

- ## Water Quality Monitoring and Notification Machine for Increase Efficiency of Water Treatment using Artificial Intelligence (JAPS.)
    - ### Skills and Technologies Used
        - **Skills and Technologies Used:**
            - Coding the Node MCU ESP-8266 (Micro-controller board) using C language.
            - Developing a wireless signal notification system for remote monitoring using Line.
            - Implementing an automatic data storage system on the cloud using Google Sheets.
            - Designing an electrical system using a gas and temperature sensor, AIS-antenna module, and lithium battery.
            - Designing a 3D model product with fire-resistant properties.
        - **Tools:**
            - Arduino IDE compiler for coding.
            - Line API for notifications.
            - Google Sheets App Script to manage the storage system.

    - ### Problem Statement
        - **Problem:** Forest fire extinguishing officers often don’t know where sparks occur in the forest until the fire has spread too large to control, especially in high-risk, hard-to-reach areas like mountain grooves. Uncontrollable forest fires cause significant damage to people in the area.
        - **Objective:** Develop a device that notifies extinguishing officers of sparks or small fires in hard-to-reach areas, increasing their control efficiency. The development focuses on affordability, durability, and reusability.

    - ### Design and Development
        - **Material Details:**
            - **Microcontroller Board:** 
                - **Arduino Uno V.3:** 32 KB memory and 1 KB SRAM (Used to read and decode data from sensors)
                - **Node MCU ESP8266 V.3:** 4 MB memory and 64 KB SRAM (Used for calculations, predictions, and internet connectivity)
            - **Gas Sensors:** 
                - **Temperature and Humidity:** DHT 11
                - **LPG:** MQ 5
                - **NH3 and Alcohol:** MQ 135
            - **Water Sensors:** 
                - **Temperature:** DS18B20
                - **DO (Dissolved Oxygen):** 5V Analog Dissolved Oxygen Sensor
                - **pH:** 5V Analog pH Meter
            - **Time Sensor:** DS3231
            - **Body:** High-grade electrical plastic box


            - **Design Process:**
                - **Coding Design:**  
                Two microcontroller boards work together in this design. The Arduino receives data from the sensors and converts the analog data to digital from seven sensors. The NodeMCU then calculates the harm rate for the bacteria based on the data from the Arduino. When this value reaches the limit, the system notifies the water treatment officer. Every 10 minutes, the device sends the average of all recorded variables to Google Sheets for storage.
                    - [[Arduino Code for Arduino IDE (.ino)]](grade10-12_picture/JAPS/Code/A1.ino)
                    - [[NodeMCU Code for Arduino IDE (.ino)]](grade10-12_picture/JAPS/Code/N1.ino)
                    - [[Google Sheet App Script (.txt)]](grade10-12_picture/JAPS/Code/Code%20Google%20sheet.txt)
                    - [[Main Calculate Function Only (.cpp)]](grade10-12_picture/JAPS/Code/main_calculate.cpp)
                - **Circuit Design:** The NodeMCU is connected to the Arduino via wires using the `Wire.h` library, and all sensors, except the time sensor, are connected to the Arduino. The power supply uses an adapter to convert from 220V to 5V, which is connected to the Arduino. The NodeMCU is powered through the Arduino's 3.3V pin.
                    <table>
                    <tr>
                        <td align="center">
                        <img src="grade10-12_picture\JAPS\disign\circuit.jpg" alt="Image 1" width="900">
                        </td>
                    </tr>
                    </table>

                - **3D Product Design:** The device is designed to float on the water in a water treatment tank, with a 220V plug connected for power supply from above. All sensors are positioned outside the box. The device must have the best water and humidity protection, ensuring no water enters inside the box.

                    <table>
                    <tr>
                        <td align="center">
                        <img src="grade10-12_picture\JAPS\disign\diagram-install-device.png" alt="Image 1" width ="430">
                        <br><strong>When Install Device</strong>
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\JAPS\disign\overview-device.png" alt="Image 1" width ="390">
                        <br><strong>Overveiew</strong>
                        </td>
                    </tr>
                    </table>

        - **Technical Details:**
            - Utilizes two microcontroller boards working together via wired connection.
            - Use data science knowled to develop a predictive function with self-learning capabilities, utilizing the maximum memory of 4 MB and 64 KB SRAM (the maximum capacity of NodeMCU ESP8266).
            - Sends notifications via Line using the LineNotification API.
            - Stores data in Google Sheets every 10 minutes, enabling historical data review.


    - ### Challenges Faced
        - **Data Noise**: Noise occurred during communication between the two boards, leading to occasional data inaccuracies. This was solved by sending data twice and verifying that both data sets are identical. If they aren't, the NodeMCU (receiver) sends a signal to the Arduino to resend the data.
        - **Memory Constraints**: The 4MB memory and 64KB SRAM were insufficient for deep calculations. This was resolved by optimizing and reducing the size of calculations.
        - **Network Issues**: The project uses a local school network, which experiences peak usage in the afternoon. This caused problems with sending data to the API and cloud. The issue was addressed by implementing a reconnect loop and using temporary memory to store data that couldn’t be immediately sent.
        - **Water Shield Design**: Ensuring a waterproof shield that could withstand the pH and water waves in the water treatment system was a challenge.


    - ### Product
        - **Overview**:
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\V1-device.png" alt="Image 1" width="500">
                <br><strong>1st Version (Test Script)</strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\V2-device.png" alt="Image 1" width="500">
                <br><strong>2nd Version (Complete Script)</strong>
                </td>
            </tr>
            </table>

        - **When Install:**
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\waterTreatmentSystem.jpg" alt="Image 1" width="500">
                <br><strong>Overview of Water Treatment System</strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\install-justMoment.png" alt="Image 1" width="500">
                <br><strong>Install Devicev (Just Moment)</strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\install-1day.png" alt="Image 1" width="500">
                <br><strong>Install Device (1 Day)</strong>
                </td>
            </tr>
            </table>

        - **Output:**
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\line-notification.png" alt="Image 1" width="200">
                <br><strong>Line Notification</strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\JAPS\product\googleSheet-table.png" alt="Image 1" width="800">
                <br><strong>Google Sheet Storage</strong>
            </tr>
            </table>

    - ### Testing and Validation
        - **Successful Data Collection and Notification**: The Water Quality Monitoring and Notification Machine was successful in collecting data from the water treatment system and sending it to Google Sheets and via Line notifications.

        - **Prediction Accuracy**: The prediction function demonstrated an accuracy of 98.21% for 15-minute predictions. This limitation was caused by the periodic operation of the air pump, which affects the intermittent properties of the water, influencing the prediction accuracy.

        - **Performance During Peak Periods**: The maximum time for data transmission during peak periods was 34.61, which is acceptable in real-world scenarios.

        - **Water Shield Weakness**: The main weakness of this version was the water shield, which was not strong enough to withstand low pH levels, high waves from the air pump, and wastewater falling from the top of the water treatment system. This caused the water shield to break quickly, leading to damage to the circuit.
        This structure emphasizes each testing and validation point clearly and adds more focus to the key

    - ### Conclusion
        The Water Quality Monitoring and Notification Machine successfully predicts water quality and alerts water treatment system officers via Line notifications, while also storing data on Google Sheets. The machine has proven to be technically usable for real-scenario with only the water shield needing improvement to ensure a stronger water seal. The device operates using an existing 220V power supply and external internet connection, making sensor maintenance is the only ongoing requirement.

    - ### Outcomes and Achievements
        - **Awards and Recognition:** 
            - Represented in a presentation to the Prime Minister of Thailand at the Thailand-Japan Student ICE Fair 2022 (national event).
            - Represented in a presentation to The Science Project Presentation of Science Fair 2023
            <br>
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\JAPS\certificate\amTJSIF.jpg" alt="Image 1" width="430">
                    <br><strong> Taking pictures with the Prime Minister of Thailand (TJSIF 2022)</strong>
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\JAPS\certificate\amSF.jpg" alt="Image 1" width="350">
                    <br><strong>Participate Science Fair 2023</strong>
                    </td>
                </tr>
            </table>

        - **Certificate:**
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\JAPS\certificate\cTJSIF.jpg" alt="Image 1" width="350">
                    <br><strong> Thailand-Japan Student ICE Fair 2022 (TJSIF)</strong>
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\JAPS\certificate\cSF.jpg" alt="Image 1" width="175">
                    <br><strong>Science Fair 2023</strong>
                    </td>
                </tr>
            </table>

    - ### Archive
        - The Lastest Code version:
            - [[Arduino Code for Arduino IDE (.ino)]](grade10-12_picture/JAPS/Code/A1.ino)
            - [[NodeMCU Code for Arduino IDE (.ino)]](grade10-12_picture/JAPS/Code/N1.ino)
            - [[Google Sheet App Script (.txt)]](grade10-12_picture/JAPS/Code/Code%20Google%20sheet.txt)
            - [[Main Calculate Function Only (.cpp)]](grade10-12_picture/JAPS/Code/main_calculate.cpp)

        - Poster
            - [Github .png](grade10-12_picture\JAPS\archieve\poster.png)
            - [Github .pdf](grade10-12_picture\JAPS\archieve\poster.pdf)
            - [Drive  .pdf](https://drive.google.com/file/d/1XIVfMGYoEI4QhCIb0kwrsKC6eTsOnnQf/view?usp=sharing)
                
        - Full Project Book (.pdf)
            - [Github](grade10-12_picture\JAPS\archieve\JAPS_completely.pdf)
            - [Drive](https://drive.google.com/file/d/1T5b9LU_VzdlB-Pj79ntWBBIYhA1CLcgt/view?usp=sharing)

            <br>
            <table>
                <tr>
                    <td align="center">
                    <a href="grade10-12_picture\JAPS\archieve\poster.png"><img src="grade10-12_picture\JAPS\archieve\poster.png" alt="Image 1" width="320"></a>
                    <br><strong> Poster </strong>
                    </td>
                    <td align="center">
                    <a href="grade10-12_picture\JAPS\archieve\JAPS_completely.pdf"><img src="grade10-12_picture\JAPS\archieve\project-book_cover.png" alt="Image 1" width="350"></a>
                    <br><strong>Project Book</strong>
                    </td>
                </tr>
            </table>

---
<br>

- ## Era Odyssey, The IDLE Game to provide knowledge about geological time (Moblie)          
    - ### Skills and Technologies Used
        - **Skills and Technologies Used:**
            - Developed an IDLE offline game using C# language with Unity.
            - Designed game database and user experience/user interface (UX/UI).
            - Created teaching media that includes text, manga, and gameplay elements.
            - Conceptualized the game's storyline, main characters, enemies, player skills, materials, and weapons.
            - Drew in-game manga, assets and materials using Procreate.
        - **Tools:**
            - Unity for coding the game.
            - Procreate for drawing manga, assets and material


    - ### Problem Statement
        - **Problem:** Currently, very few games feature ancient creatures beyond dinosaurs. This has inspired us to create a game that showcases a broader range of prehistoric life forms.
        - **Objective:** Develop an educational and entertaining game that introduces players to life forms from the early stages of the solar system and different geological periods. The game will include a unique four-element skill system, various materials, and weapons, all set within the IDLE game catagory.

    - ### Design, Development and Product
        - **Game Website:** 
             - [Main-era-odyssey-ciqb.vercel.app](https://main-era-odyssey-ciqb.vercel.app/assets/Home.html)
             - [Github repository](https://github.com/Jakkarin-Promsee/Era-Odyssey)
        - **Coding Details:** [Github Code repository](https://github.com/Jakkarin-Promsee/Unity-EraOdesey/tree/main) 
            - **Data steam system:** 
                - **Scriptable Object:** Used to write base data for key properties of each type, such as materials, weapons, and skills. This ensures that all essential attributes, like pictures, object names, details, periods, and quantities, are centralized.
                - **Frame Functionality:** An additional frame was created to manage functions such as incrementing, decrementing, setting values to defaults, assigning internal variables (object properties) to specific values, calculating material requirements for upgrades, damage calculation, cooldowns, and more.
                - **Main Scripts:** Developed three main scripts to handle groups of scriptable objects (materials, weapons, skills), enabling functions like calling objects of all types, saving to JSON, reading and replacing data from JSON, crafting weapons, upgrading skills, etc.
                - **Master Script:** A top-priority script was developed to access and control these three main scripts. This master function manages key features such as save/load functionality, hashing and decoding JSON data, and integrates seamlessly with the combat script for smooth gameplay.

            - **Combat system:**
                - **Player Script:** Works with the Master Script to call the current equipment (weapon) and calculate the damage and properties for attacks, which are then processed in the Enemy Script. This script also manages the display of player stats (HP, ATK, SP, etc.) and controls the player's animations on screen. It handles actions like picking up items and works in integrates with the Skill Script and Current use Equipments Pop Up.

                - **Skill Script:** Collaborates with both the Master Script and Player Script. It handles special attacks based on the four elements—earth, water, wind, and fire such as emitting a large water wave, shooting fireballs, summoning flying sword clones to attack, etc. This script also integrates with the Information Pop-Up system and Skill Slot Script, allowing the player to select up to 8 skills for manual or automatic use. The script calculates skill damage using the Player Script and retrieves skill properties (e.g., image, cooldown) from the Master Script.

                - **Stage Script:** Manages the enemy data for each stage. Since the stage and enemy properties are fixed, the player's development is the only changing factor. This script randomly summons normal enemies and specific boss enemies at different periods of time.

                - **Enemies Script:** Works with the Stage Script, which provides enemy properties such as HP, damage, item drops, experience, speed, etc. When an enemy dies, this script triggers the Material Pick Script to summon material items on the screen.

                - **Material Pick Script:** Receives material drop information from the Enemies Script and moves the material toward the player. When the material reaches the player, the Master Script updates the material count in the database.
                

            - **Information Pop Up system:**
                - **Materials Detail:** The UX/UI displays all materials in the game, sorted into four columns, with each period featuring four materials. When users click on a material slot, a pop-up appears showing the material's name, period, amount, and additional details.

                - **Weapons Detail:** Similar to the materials section, the UX/UI displays all weapons in the game sorted by four columns, with each period featuring four weapons. When users click on a weapon slot, a pop-up appears with the weapon's name, period, amount, details, and two buttons: "Equip" and "Craft." Clicking "Craft" opens a pop-up with crafting details, and clicking "Equip" updates the current equipment display.

                - **Craft Detail:** This pop-up contains the required materials for crafting, including the amount needed, material images, and names. The pop-up also shows how much damage will be increased by crafting. When users click "Craft," the pop-up sends a signal to the Player Script to execute the crafting function in the Master Script.

                - **Current Equipments:** The UX/UI provides six slots for equipment: Sword 1, Sword 2, Hat, Shirt, Pants, and Shoes. When users click on any of these slots, a pop-up displaying the equipped item's details will appear. The script will send a signal to the Player Script to calculate damage in conjunction with the Master Script.

                - **Slot Skills and Detail:** The UX/UI displays all available skills, separated into four columns based on their elemental type. When users click on a skill slot (skill image), a pop-up will show skill details, and users can choose to use or upgrade the skill to increase its abilities. Clicking "Use Skill" sends the skill data to the current skill slots for activation.

                - **Current Skill Slots:** The UX/UI provides an eight-slot skill bar where players can drag and drop skills to use in combat. The selected skills will be displayed in the slots and can be activated either by clicking on them or by using the automatic skill button. Once a skill is activated, it sends a signal to the Skill Script, which runs the corresponding function on the Player Script.

                - **Period Information:** This is the primary pop-up that displays information for each period. Each chapter is unlocked as players progress through the game. The pop-up provides details about important events, the environment, creatures, etc., related to that period.

                - **Period Quiz:** This is a quiz feature that challenges users' knowledge of the periods. The quiz displays sentences based on the period information, and users must answer whether the statement is correct or incorrect within a set time. If the user answers incorrectly, the quiz ends, displaying their score and an explanation of why the answer was wrong.

        - **Story Details:** [Story on Web page](https://main-era-odyssey-ciqb.vercel.app/assets/Home.html)
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\1.png" alt="Image 1" width="400">
                <br><strong><1></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\2.png" alt="Image 1" width="400">
                <br><strong><2></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\3.png" alt="Image 1" width="400">
                <br><strong><3></strong>
                </td>
            </tr>
            </table>

            1. *The Saxabra* is like a central hub of all human knowledge. It was created through the collaboration of countries around the world by building a large island from reclaimed land. On top of this island, a city was constructed. This city functions like a huge science exhibit or a giant laboratory. Its goal is to bring researchers from all over the world together in one place to study human potential. In the center of the city stands a large center known as The Briatis, which represents the essence of the city.

            2. The Briatis is where scientists, researchers, and experts from different fields live and work together. It also provides the main energy for the whole island and is a center for creating new inventions, theories, and many other innovations, some of which are kept secret. Only a few high-ranking officials know about the secrets inside The Briatis.

            3. Everyone understands that "human resources" are very important. They are like variables that can change by themselves at any time. Many people want to contribute to the development of humanity, but due to various factors, they end up being just workers in white lab coats, carrying things around. They are not much different from robots. Thankfully, there is a high-level leader who rejected the use of robots. Without him, I wouldn’t be standing here showing my skills, and neither would others.

            <br><br><table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\4.png" alt="Image 1" width="400">
                <br><strong><4></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\5.png" alt="Image 1" width="400">
                <br><strong><5></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\6.png" alt="Image 1" width="400">
                <br><strong><6></strong>
                </td>
            </tr>
            </table>

            4. Hello everyone, I’m Demain H. Cover, a standout employee in the Common General Work Section 5. I’m not just boasting—my colleagues are smart, but they don’t always think for themselves. I get it. Many who come here don’t become selected researchers and don’t have research achievements or recognized qualifications. Working here at this "simulated paradise" to fulfill dreams might be a good option.
            <br><br>
            While working here, I’ve seen many employees start to lose their individuality and ability to think critically. It might be because they spend their time cleaning, organizing documents and energy, or following the orders of researchers they assist. I’m also surprised at how many employees act like robots, just following orders without question. Maybe something else is influencing them. I’m just speculating.

            5. The researchers here are all geniuses selected to work together on this island. But I’ve heard that even among these geniuses, there are some who are considered the ultimate of the ultimate—“at the peak of ideal learning.” Let me tell you a story.
            <br><br>
            While I was walking to review the progress of a research project, I heard that there are four people who are recognized as the best of the best. They are as mysterious as legends. The technology and research they work on are beyond imagination and are kept as top secrets. Some researchers speculate that one of them might be able to draw energy or create objects from human imagination, or that another can control time. These rumors might seem exaggerated, but on this island, they could very well be true. The idea of technology that could conquer even gods is quite intriguing.

            6. It seems I’ve entered the research room I was assigned to. It looks like the Si-2505 might be some kind of door. It’s strange because it can look different each time you glance away and then look back. It’s built with odd technology and materials that don’t match the room’s atmosphere. The blue light coming from it makes me feel uneasy. I think I’ll quickly record the data and get out of this room.

            <br><br><table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\7.png" alt="Image 1" width="400">
                <br><strong><7></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Story\8.png" alt="Image 1" width="400">
                <br><strong><8></strong>
            </tr>
            </table>

            7. Before I could analyze the components of the experiment, it suddenly seemed to activate on its own. The strange blue light was so bright that I felt like I needed to buy those light-filtering glasses advertised on the island. Along with the odd sounds affecting my senses, I didn’t know what to do. It felt like this might be a plan to silence me, or maybe my past actions are catching up with me now. The light was so intense it turned everything white. It felt like I was being engulfed and put to sleep by the swirling, strange sounds around me.

            8. Ah... that’s the story of how I ended up sent back to some unknown era of the world by that machine. Maybe this is the result of me not paying attention to geology. But it’s in the past now. Given my skills, which are like those of a protagonist in a survival game, I think I have a good chance of surviving and returning to the present. Thanks for listening to my complaints. Keep an eye out to see if I can make it back to the present... Yikes!

        - **Creature Details:** [Creature Deatials on Web page](https://main-era-odyssey-ciqb.vercel.app/assets/Monster.html)
        <br>**Example 8 of creature we used.**
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\1.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\2.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\3.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\4.png" alt="Image 1" width="400">
            </tr>
            </table>
            <table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\5-1.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\5-2.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\6.png" alt="Image 1" width="400">
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\monter\7.png" alt="Image 1" width="400">
            </tr>
            </table>

        - **Manga Details:** 
            - [Github (.pdf)](grade10-12_picture\EraOdyssey\manga.pdf)
            - [Drive (.pdf)](https://drive.google.com/file/d/1Uix36YkKzBhnvanWOvy8TiV5JEy_0b82/view?usp=sharing)
            - [Manga on Web page](https://main-era-odyssey-ciqb.vercel.app/assets/Information.html)

            <br><table>
            <tr>
                <td align="center">
                <a href="grade10-12_picture\EraOdyssey\manga.pdf"><img src="grade10-12_picture\EraOdyssey\manga.png" alt="Image 1" width="250"></a>
                <br><strong>Information Manga</strong>
                </td>
            </tr>
            </table>

        - **Information in each period:**
            - [CH1-The Solar Systerm Form](/grade10-12_picture/EraOdyssey/Information%20in%20each%20period/Temporary1-The%20Solar%20Systerm%20Form.txt)
            - [CH2-The earth born](/grade10-12_picture/EraOdyssey/Information%20in%20each%20period/Temporary2-The%20earth%20born.txt)
            - [CH3-Precambrain Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary3-Precambrain.txt)
            - [CH4-Cambrian Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary4-Cambrian.txt)
            - [CH5-Ordovicain Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary5-Ordovicain.txt)
            - [CH6-Silurian Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary6-Silurian.txt)
            - [CH7-Devonian Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary7-Devonian.txt)
            - [CH8-Caboniferous Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary8-Caboniferous.txt)
            - [CH9-Permian Period](grade10-12_picture\EraOdyssey\Information%20in%20each%20period\Temporary9-Permian.txt)

    - ### Challenges Faced
        - **Creating a Complex Database:** Developing the database required a deep understanding of object-oriented programming (OOP) within the Unity environment. Managing a vast number of data types and categories made the data structure quite large. Each script had to be carefully connected, which added significant complexity and challenge to the process.

        - **Combat System Integration:** Since this project involved multiple team members, integrating the data stream with the combat system was particularly challenging. The combat system needed to pull data from the database while simultaneously interacting with the UX/UI slots. As a result, the main function controlling all player actions became quite large and required additional time to integrate with other code.

        - **Asset Design:** As beginners in game design, we found it challenging to transition from designing on paper to creating digital assets. Designing characters, items, and environments for the game required us to develop new skills and overcome various obstacles.

        - **Unity Tools Issues:** As novices in using Unity, we often encountered errors within the tool itself, not necessarily in the code. These technical issues with Unity slowed our progress significantly, as we had to spend extra time troubleshooting and resolving problems unrelated to our programming efforts.

    - ### Game Product
        Due to the group members parting ways to attend different universities, the development of this game was stop. Although it is playable on Android devices, some features are still incomplete, leaving the game unfinished. However, the product remains a testament to our core vision and inspiration, capturing the essence of what we aimed to achieve.

        - **APK Downloading for android:** [Go to Webpage to download](https://main-era-odyssey-ciqb.vercel.app/assets/Play.html)

        - **Overview**: The character will attack automatically, and the player must clear each stage. When enemies are defeated, they will drop experience points (EXP), which will increase the player's stats, as well as materials that can be used to craft new weapons and armor to further upgrade the player's status. Users need to strategize and select the right set of weapons and armor to face the boss in each period to progress to the next stage.
            1. Opening the game.
            2. Enemies will spawn from the stage.
            3. The character will attack automatically. When enemies die, they will drop EXP and materials.
            4. Players must use these materials to upgrade weapons and armor, planning their equipment to grow stronger.
            5. When players have sufficient equipment, they can challenge the stage boss. If they win, a new period will unlock with new materials, items, and more.

            <br><table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\opening\0_opening.jpg" alt="Image 1" width="200">
                <br><strong><1></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\opening\1_gameBegining.jpg" alt="Image 1" width="200">
                <br><strong><2></strong>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\opening\2_attacking.jpg" alt="Image 1" width="200">
                <br><strong><3></strong>
                </td>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\opening\3_status.jpg" alt="Image 1" width="200">
                <br><strong><4></strong></strong>
                </td>
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\opening\4_boss.jpg" alt="Image 1" width="200">
                <br><strong><5></strong>
                </td>
            </tr>
            </table>

        - **Material:** 
            1. Players can view all materials in the inventory slot. Items that have not been obtained will appear as black icons, indicating they are unknown.
            2. When players press on an unknown item icon, the information will show as "Unknown."
            3. When players press on an obtained item icon, the full item information (name, description, etc.) will be displayed.

            <br><table>
            <tr>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\material-slots\0_slot-material.jpg" alt="Image 1" width="200">
                <br>[1]
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\material-slots\1_unknown-material-information.jpg" alt="Image 1" width="200">
                <br>[2]
                </td>
                <td align="center">
                <img src="grade10-12_picture\EraOdyssey\Game-image\material-slots\2-material-information.jpg" alt="Image 1" width="200">
                <br>[3]
                </td>
            </tr>
            </table>

        - **Weapon and Armmor:** Players can view all equipment in the weapon and armor slots. Equipment that has not been obtained (crafted) will appear as black icons, indicating they are unknown. When players click on a crafted item, it will be equipped and shown in the current equipment slot, increasing the player's stats.
            1. **Weapon Slots:** Displays all weapons, both obtained and unknown.
            2. **Armor Slots:** Displays all armor pieces, both obtained and unknown.
            3. **Current Equipment Slots:** Shows the currently equipped weapon and armor, which contribute to the player's stats.
            - **Slot:** 
                <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\0 _slots-weapon.jpg" alt="Image 1" width="200">
                    <br>Slot Weapon
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\0-slot-armor.jpg" alt="Image 1" width="200">
                    <br>Slot Armor
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\0_slots-Equipment.jpg" alt="Image 1" width="200">
                    <br>Slot Current Equipment
                    </td>
                </tr>
                </table>
            - **Weapon craft:**
                <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\1-unknownWeapon-information.jpg" alt="Image 1" width="200">
                    <br>Unknown Information
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\2-unknownWeapon-craft.jpg" alt="Image 1" width="200">
                    <br>Weapon Crafting
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\3-wapon-craft.jpg" alt="Image 1" width="200">
                    <br>Weapon Upgrading
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\4-weapon-information.jpg" alt="Image 1" width="200">
                    <br>Weapon Information
                    </td>
                </tr>
                </table>

                <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\5-armor-craft.jpg" alt="Image 1" width="200">
                    <br>Armor upgrade
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\weapon-slots\6-armor-information.jpg" alt="Image 1" width="200">
                    <br>Armor Information
                </tr>
                </table>
        - **Skills:** This future isn't complete successfully, It's still be the consept in damage equation use by non-graphic assets, and many function is not done. However, this skills is enable to use.
            - **Select skill:**
                <table>
                    <tr>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\0_skill-slot.jpg" alt="Image 1" width="200">
                        <br>Skill Slotes
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\1_skill-information.jpg" alt="Image 1" width="200">
                        <br>Skill Information
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\2_skill-choose.jpg" alt="Image 1" width="200">
                        <br>Choosing to skill bar
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\4_on-autoskill.jpg" alt="Image 1" width="200">
                        <br>Open auto skill use
                        </td>
                    </tr>
                </table>

            - **Using Skill:**
                <table>
                    <tr>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\5_skill-use.jpg" alt="Image 1" width="200">
                        <br>Ex1 Skill
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\5_skill-use2.jpg" alt="Image 1" width="200">
                        <br>Ex2 Skill
                        </td>
                        <td align="center">
                        <img src="grade10-12_picture\EraOdyssey\Game-image\skill-slots\5_skill-use3.jpg" alt="Image 1" width="200">
                        <br>Ex3 Skill
                    </tr>
                </table>

        - **Challenge boss to unlock new period:** Players can click to select a period and choose the one they want to challenge. Players can battle the boss of each period, and if they win, a new locked period will be unlocked, granting access to new materials, weapons, and armor.
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\0_stage_choose.jpg" alt="Image 1" width="200">
                    <br>Choose Period to Play
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\4_boss.jpg" alt="Image 1" width="200">
                    <br>Fight Period Boss
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\1_new-stage.jpg" alt="Image 1" width="200">
                    <br>Go to New Period
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\New-boss2.jpg" alt="Image 1" width="200">
                    <br>Fight New Period Boss
                </tr>
            </table>
        
        - **Information:** Players can choose to read and test their knowledge of each period. The quiz will randomly present facts from each period, and players must select whether they are true or false. If the player loses, the quiz will stop and show the reason for their loss.
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\0_stage.jpg" alt="Image 1" width="200">
                    <br>Period Information
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\22_quiz-chapter.jpg" alt="Image 1" width="200">
                    <br>Period Quiz
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\24_example-quiz.jpg" alt="Image 1" width="200">
                    <br>Example Quiz
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Game-image\25_example-answer.jpg" alt="Image 1" width="200">
                    <br>Answer Show
                </tr>
            </table>
                

    - ### Conclusion
        Era Odyssey, an IDLE game designed to provide knowledge about geological time, was not fully completed. The development stopped as the group members pursued studies at different universities. Although the game is playable on Android devices, several features remain unfinished. Despite this, we are proud of what we achieved, given our knowledge, age, and the time constraints we faced. The game aligned with our vision, but we lacked the experience and time to fully bring it to life. This project remains a valuable learning experience, culminating in a gold medal presentation. We gained significant knowledge in algorithms, coding, drawing, and project planning through this stuggle.

    - ### Outcomes and Achievements
        - **Awards and Recognition:** Represented in the presentations at The 3rd PCSHS Science Symposium 2023 and received the Gold Award in the computer presentation category.
            <br>
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Presentation\P2.JPG" alt="Image 1" width="430">
                    <br><strong> Science Symposium 2023 </strong>
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Presentation\P1.JPG" alt="Image 1" width="380">
                    <br><strong> Presentation on technology event </strong>
                    </td>
                </tr>
            </table>

        - **Certificate:**
            <table>
                <tr>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Presentation\Cer.jpg" alt="Image 1" width="350">
                    <br><strong> Science Symposium 2023 </strong>
                    </td>
                    <td align="center">
                    <img src="grade10-12_picture\EraOdyssey\Presentation\med.png" alt="Image 1" width="187">
                    <br><strong>Gold Medal</strong>
                    </td>
                </tr>
            </table>

    - ### Archive
        - Game Website
             - [**Main-era-odyssey-ciqb.vercel.app**](https://main-era-odyssey-ciqb.vercel.app/assets/Home.html)
             - [Dowload Game (android)](https://main-era-odyssey-ciqb.vercel.app/assets/Play.html)
             - [Github repository](https://github.com/Jakkarin-Promsee/Era-Odyssey)

        - Coding Details
            - [Github Code repository](https://github.com/Jakkarin-Promsee/Unity-EraOdesey/tree/main) 

        - Our Note (.pdf)
            - [Github](grade10-12_picture\EraOdyssey\Archive/Era-Odyssey_13%20(1).pdf)
            - [Drive](https://drive.google.com/file/d/1Tkin27xTOe03IUMdacgwcbUMGCWm71J5/view?usp=sharing)

        - Poster
            - [Github .png](grade10-12_picture\EraOdyssey\Archive\Poster.png)
            - [Github .pdf](grade10-12_picture\EraOdyssey\Archive\EraOdyssey-poster.pdf)
            - [Drive  .pdf](https://drive.google.com/file/d/1fLO82Z6p8c3w2_UoOv0RFoMHkIAcN7gc/view?usp=sharing)
                
        - Academic articles (.pdf)
            - [Github](grade10-12_picture\EraOdyssey\Archive/Academic-articles.pdf)
            - [Drive](https://drive.google.com/file/d/1TfpMuQfXKr1hJJAq4NO01Vl2_YBRn2z5/view?usp=drive_link)

            <br>
            <table>
                <tr>
                <td align="center">
                    <a href="grade10-12_picture\EraOdyssey\Archive\Era-Odyssey_13 (1).pdf"><img src="grade10-12_picture\EraOdyssey\Archive\Era-Odyssey_13-cover.png" alt="Image 1" width="320"></a>
                    <br><strong> Poster </strong>
                    </td>
                    <td align="center">
                    <a href="grade10-12_picture\EraOdyssey\Archive\Poster.png"><img src="grade10-12_picture\EraOdyssey\Archive\Poster.png" alt="Image 1" width="300"></a>
                    <br><strong> Poster </strong>
                    </td>
                    <td align="center">
                    <a href="grade10-12_picture\EraOdyssey\Archive\Academic-articles.pdf"><img src="grade10-12_picture\EraOdyssey\Archive\Academic-cover.png" alt="Image 1" width="350"></a>
                    <br><strong>Project Book</strong>
                    </td>
                </tr>
            </table>

---
<br>