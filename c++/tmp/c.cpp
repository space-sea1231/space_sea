// 将键绑定放在此文件中以覆盖默认值
[
    {
        "key": "ctrl+d",
        "command": "editor.action.deleteLines",
        "when": "textInputFocus && !editorReadonly"
    },
    {
        "key": "ctrl+shift+k",
        "command": "-editor.action.deleteLines",
        "when": "textInputFocus && !editorReadonly"
    },
    {
        "key": "ctrl+q",
        "command": "editor.action.addSelectionToNextFindMatch",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+d",
        "command": "-editor.action.addSelectionToNextFindMatch",
        "when": "editorFocus"
    },
    {
        "key": "numpad9",
        "command": "extension.getNextPage",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+.",
        "command": "-extension.getNextPage",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+;",
        "command": "-extension.getJumpingPage"
    },
    {
        "key": "ctrl+up",
        "command": "extension.displayCode"
    },
    {
        "key": "ctrl+m",
        "command": "-extension.displayCode"
    },
    {
        "key": "numpad9",
        "command": "extension.getPreviousPage",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+,",
        "command": "-extension.getPreviousPage",
        "when": "editorTextFocus"
    },
    {
        "key": "numpad9",
        "command": "vscode-mini-book.goTo",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+.",
        "command": "-vscode-mini-book.goTo",
        "when": "editorFocus"
    },
    {
        "key": "numpad9",
        "command": "vscode-mini-book.back",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+,",
        "command": "-vscode-mini-book.back",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+up",
        "command": "vscode-mini-book.bossKey",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+m",
        "command": "-vscode-mini-book.bossKey",
        "when": "editorFocus"
    },
    {
        "key": "ctrl+r",
        "command": "-vscode-mini-book.load",
        "when": "editorFocus"
    },
    {
        "key": "alt+2",
        "command": "-statusRead.getNextLine",
        "when": "editorTextFocus"
    },
    {
        "key": "alt+1",
        "command": "-statusRead.getPreviousLine",
        "when": "editorTextFocus"
    },
    {
        "key": "alt+3",
        "command": "-statusRead.bossHide",
        "when": "editorTextFocus"
    },
    {
        "key": "alt+4",
        "command": "-statusRead.automatic",
        "when": "editorTextFocus"
    },
    {
        "key": "alt+6",
        "command": "-statusRead.reLoad",
        "when": "editorTextFocus"
    },
    {
        "key": "numpad9",
        "command": "statusRead.jumpPage",
        "when": "editorTextFocus"
    },
    {
        "key": "alt+5",
        "command": "-statusRead.jumpPage",
        "when": "editorTextFocus"
    }
]