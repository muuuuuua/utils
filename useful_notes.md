# 开发环境初始化

## zsh
### 安装oh-my-zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    
### 安装autojump
https://github.com/wting/autojump

### 安装zsh-autosuggestions
https://github.com/zsh-users/zsh-autosuggestions/blob/master/INSTALL.md  
修改~/.oh-my-zsh/custom/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh  
typeset -g ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE='fg=6'

plugins=(git autojump zsh-autosuggestions)

## tmux
### Tmux Plugin Manager
https://github.com/tmux-plugins/tpm

### tmux重启自动恢复现场
首先要安装tpm  
https://github.com/tmux-plugins/tmux-continuum

# 其他
### git log显示乱码
export LESSCHARSET=utf-8

### mac使用linux的date
brew install coreutils
alias date='/usr/local/bin/gdate'
