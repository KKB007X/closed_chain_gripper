from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction, SetEnvironmentVariable
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import xacro


def generate_launch_description():

    pkg = get_package_share_directory('gripper_description')

    urdf_file = os.path.join(
        pkg,
        'urdf',
        'gripper_description.urdf'
    )

    controllers_file = os.path.join(
        pkg,
        'config',
        'controllers.yaml'
    )

    robot_desc = xacro.process_file(
        os.path.join(
            pkg,
            'urdf',
            'gripper_description.urdf.xacro'
        ),
        mappings={
            'controllers_file': controllers_file
        }
    ).toxml()

    gz_resource = SetEnvironmentVariable(
        name='GZ_SIM_RESOURCE_PATH',
        value=os.path.join(pkg, '..')
    )

    return LaunchDescription([

        gz_resource,

        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{
                'robot_description': robot_desc,
                'use_sim_time': True
            }],
            output='screen'
        ),

        ExecuteProcess(
            cmd=['gz', 'sim', '-r'],
            output='screen'
        ),

        TimerAction(
            period=2.0,
            actions=[
                Node(
                    package='ros_gz_sim',
                    executable='create',
                    arguments=[
                        '-topic',
                        'robot_description',
                        '-name',
                        'gripper',
                        '-z',
                        '0.2',
                        '-R',
                        '3.14'
                    ],
                    output='screen'
                )
            ]
        )
    ])