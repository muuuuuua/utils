### 安装oh-my-zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    
### 安装autojump
https://github.com/wting/autojump

### 安装zsh-autosuggestions
https://github.com/zsh-users/zsh-autosuggestions/blob/master/INSTALL.md  
修改~/.oh-my-zsh/custom/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh  
typeset -g ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE='fg=6'

plugins=(git autojump zsh-autosuggestions)
