#!/usr/bin/env osascript -l JavaScript
// osacompile -l JavaScript -o finderterm.app terminal.scpt
// Info.plist: 'Application is agent (UIElement)' = 'YES'

/*
 * 获取最前面的 finder 窗口的所在目录
*/
function pathOfFinderWindow(finder) {
  if (finder.windows.length) {
    // file:///home/eph/Desktop
    return decodeURI(finder.windows[0].target().url().slice(7));
  } else {
    return '';
  }
}

// 用单引号包围，并把所有的 "'" 替换为 "'\''"
function shellescape(string) {
  return "'" + string.replace("'", "'\\''") + "'"
}

(function() {
  let app = Application.currentApplication();
  app.includeStandardAdditions = true;
  let se = Application('System Events');

  let finder = Application('Finder');
  let cwd = pathOfFinderWindow(finder);
  let terminal = Application('terminal');
  let cmd = 'cd ' + shellescape(cwd) + ' && open -a Terminal'
  //let cmd = 'open -a Terminal ' + shellescape(cwd);
  terminal.doScript(cmd);
})();
