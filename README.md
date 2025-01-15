**git初始化**  
`git init`  
**添加文件到缓存区**  
`git add .`  
**查看缓存区状态**  
`git status`  
**切换到master分支**  
`git checkout master`  
**强制转换为main分支**  
`git branch main master -f`  
**切换到master分支**  
`git checkout main`  
**推送本地仓库到远程仓库**  
`git push origin main -f`  

**获取本地ssh**  
`ssh-keygen -t rsa -C "minecraftyhbl@outlook.com"`  
**添加远程仓库为origin**  
`git remote add origin git@github.com:space-sea1231/space_sea.git`  
**添加上传者的信息**  
`git config --global user.email "minecraftyhbl@outlook.com"`  
`git config --global user.name "space_sea"`  
**我的远程仓库ssh**  
`git@github.com:space-sea1231/space_sea.git`  
**lfs建立跟踪**  
`git lfs track "*.文件后缀"`  
>在此之后要重新`git add .`  
