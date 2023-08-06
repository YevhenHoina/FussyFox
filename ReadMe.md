# Instalation

To install this shit, you need to setup yout git repository correctly

Firstly download Git LFS here -> https://git-lfs.com

## Manual install
1. Navigate to your Unreal project folder
E. g.:
```console
cd C:\Users\USERNAME\Documents\Unreal Projects\FussyFox
```
2. Setup your git repository folder
```console
git init
git lfs install
```
3. Add Large file storage tracking
```Console
git lfs track "Content/Assets**"
git lfs track "Content/Maps**"
git checkout -b main
git pull https://github.com/YevhenHoina/FussyFox main
```
## Auto install

1. Navigate to your Unreal projects folder
E. g.:
```console
cd C:\Users\USERNAME\Documents\Unreal Projects
```
2. Clone the repository under the FussyFox folder
```console
git clone https://github.com/YevhenHoina/FussyFox FussyFox
```


