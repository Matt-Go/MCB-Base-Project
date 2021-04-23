# Git Bash Installation

Download Git Bash [https://git-scm.com/downloads](https://git-scm.com/downloads).
Run the installer.
Accept the terms and conditions, and run through the installer.
Notable settings:

- Select an additional icon on the Desktop
- Use the Vim editor (or Notepad++, or Nano)
- **Checkout Windows-style, commit Unix-style line editings**

# Cloning the Repo

Using git bash, clone the repo to your computer.

```
git clone https://gitlab.com/aruw/MCB_Base_Project.git
```
You'll need to type your gitlab username and password.
Change to the cloned directory.
```
cd MCB_Base_Project
```
From here all the git commands will work.

# Important commands

```
git branch -a
```
Lists all the branches as part of our repositor, on origin and on your computer.

```
git checkout -b tarkan_buzzer origin/tarkan_buzzer
```
Creates a branch called `tarkan_buzzer` that will have upstream target
`origin/tarkan_buzzer`.
