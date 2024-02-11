# Robot Types

## Content
In this folder you can find all my robot projects, which I developed using the **ROS2 Foxy** distribution and different **programming languages**. The table shows the development process for each robot and algorithm. The columns of the table illustrate the different robot algorithms and techniques, like Navigation, Control etc. The status of the development process is divided into the categories **---**, **implemented**, **inoperative** and **functional**. Note that implemented differs from functional, in that the operation was only implemented and not tested for functionality in Gazebo, but only in RViz. In contrast, not working means that the operation was implemented and tested, but has some issues.

## Notes

### Explanation of the development status 
<table>
    <tr>
        <th>Status</th>
        <th>Symbol</th>
        <th>Details</th>
    </tr>
    <tr>
        <td>functional</td>
        <td>**func**</td>
        <td>The function has been implemented and works properly. For example, the robot was designed and works in RViz, Gazebo and the desired algorithms like navigation etc.</td>
    </tr>
    <tr>
        <td>implemented</td>
        <td>impl</td>
        <td>The function has been implemented, but not tested. For simulation, this means that the robot gets spawned in Gazebo but sensors and other devices are not working now.</td>
    </tr>
    <tr>
        <td>inoperative</td>
        <td>*!inop*</td>
        <td>The function has been implemented, tested but doesn't work now.</td>
    </tr>
</table>

### Development status for each robot
<table>
    <tr>
        <th>Name</th>
        <th>Type</th>
        <th>Design</th>
        <th>Control</th>
        <th>Simulation</th>
        <th>Navigation</th>
        <th>Manipulation</th>
        <th>Vision</th>
        <th>AI</th>
    </tr>
    <tr>
        <td>My Mobile Manipulator</td>
        <td>Mobile Manipulator</td>
        <td>**func**</td>
        <td>**func**</td>
        <td>impl</td>
        <td>---</td>
        <td>---</td>
        <td>---</td>
        <td>---</td>
    </tr>
</table>