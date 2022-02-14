from setuptools import find_packages, setup

setup(
    name='dashboard',
    version='0.1-alpha',
    packages=find_packages(),
    include_package_data=True,
    zip_safe=False,
    install_requires=[
        'flask',
    ],
)
