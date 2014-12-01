This package contains code snippets for everday tasks and demonstrates the usage of some useful c++ tools.

# Install ROS hydro
[How to install ROS](http://wiki.ros.org/ROS/Installation)

# Install pre-requisites
``` bash
sudo apt-get install python-pip
sudo pip install catkin-tools 
sudo apt-get install python-rosinstall
```

# Create catkin workspace managed by rosws
``` bash
cd ~
mkdir -p catkin_ws/src
cd ~/catkin_ws/src
rosws init
// Add repositories to workspace
rosws set Schweizer-Messer https://github.com/ethz-asl/Schweizer-Messer --git
// ... and more
rosws update
catkin config
```

Add setup.bash to your bashrc:
``` bash
echo 'source ~/catkin_ws/devel/setup.bash' >> ~/.bashrc
```

# Building packages
You have to be in your catkin workspace to execute the ```catkin build``` command:
``` bash
cd ~/catkin_ws
catkin build <package_name>
```
You can set up a convenient alias in your .basrc to avoid the required directory change. Add this line to your .bashrc:
``` bash
alias catkin_build='catkin build --workspace /path/to/your/catkin_ws'
```

# Useful catkin build options
``` bash
catkin build --force-cmake <package_name> -DCMAKE_BUILD_TYPE=Release
```

# Compile and execute the unit test
``` bash
catkin build --catkin-make-args run_tests
```

# Student templates
Student templates for the presentation and the latex report can be found
[here](https://github.com/ethz-asl/asl-student-templates).

# Evaluation criteria
Please ask your supervisor for the evaluation criteria of your work.
