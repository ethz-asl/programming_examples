This package contains code snippets for everday tasks and demonstrates the usage of some useful c++ tools.

# Install ROS hydro
[How to install ROS](http://wiki.ros.org/ROS/Installation)

# Install pre-requisites
``` bash
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
rosws update
catkin_init_workspace
```

Add setup.bash to your bashrc:
``` bash
echo 'source ~/catkin_ws/devel/setup.bash' >> ~/.bashrc
```

# Building this package
``` bash
cd ~/catkin_ws
catkin build
```

# Run the unit test
``` bash
catkin build example_package --catkin-make-args run_tests
```

or

``` bash
catkin build example_package_python --catkin-make-args run_tests
```

# Student templates
Student templates for the presentation and the latex report can be found
[here](https://github.com/ethz-asl/asl-student-templates).

# Evaluation criteria
Please ask your supervisor for the evaluation criteria of your work.
