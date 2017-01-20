'''
Template for creating new gspeak apps.
'''
from __future__ import print_function
import errno
import jinja2
import os

def ensure_dir(path):
    '''
    mkdir -p for python
    '''
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise


def obi_new(**kwargs):
    '''
    obi new gspeak project_name --gspeak=g_speak_home
    '''
    pairs = list([
        [os.path.join("debian", "changelog"), "changelog"],
        [os.path.join("debian", "compat"), "compat"],
        [os.path.join("debian", "control"), "control"],
        [os.path.join("debian", "rules"), "rules"],
        ["set-gspeak.sh", "set-gspeak.sh"],
        ["g-speak.dat", "g-speak.dat"],
        [os.path.join("src", "main.cpp"), "main.cpp"],
        [".gitignore", "gitignore"],
        ["project.yaml", "project.yaml"],
        ["three-screen.protein", "three-screen.protein"],
        ["three-feld.protein", "three-feld.protein"],
        ["CMakeLists.txt", "CMakeLists.txt"]])
    env = jinja2.Environment(loader=jinja2.PackageLoader(__name__),
                             keep_trailing_newline=True)
    project_path = kwargs['project_path']
    for file_path, template_name in pairs:
        file_path = os.path.join(project_path, file_path)
        ensure_dir(os.path.dirname(file_path))
        # look for the template in any of the envs
        # break as soon as we find it
        try:
            template = env.get_template(template_name)
            with open(file_path, 'w+') as fil:
                fil.write(template.render(kwargs))
        except jinja2.TemplateNotFound:
            print("Warning: Could not find template {0}".format(template_name))
    return 0
