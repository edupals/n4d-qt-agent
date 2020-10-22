# -*- coding: utf-8 -*-
from distutils.core import setup
from distutils.extension import Extension
import os
import subprocess

setup(  name             = "n4d agent",
        version          = "1.0",
        author           = "Enrique Medina Gremaldos",
        author_email     = "quiqueiii@gmail.com",
        url              = "https://github.com/edupals/n4d-qt-agent",
        package_dir      = {'': '.'},
        packages         = ['n4d','n4d.agent']
     )


