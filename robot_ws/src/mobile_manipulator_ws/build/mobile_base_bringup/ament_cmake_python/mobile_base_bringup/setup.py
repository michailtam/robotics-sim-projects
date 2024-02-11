from setuptools import find_packages
from setuptools import setup

setup(
    name='mobile_base_bringup',
    version='0.0.0',
    packages=find_packages(
        include=('mobile_base_bringup', 'mobile_base_bringup.*')),
)
