#!/usr/bin/env osascript -l JavaScript

(function() {
  let app = Application.currentApplication();
  app.includeStandardAdditions = true;
  let se = Application('System Events');
  if (Application('iTerm 2').running()) {
    let iTerm2 = Application('iTerm 2');
    iTerm2.createWindowWithDefaultProfile();
  } else {
    let iTerm2 = Application('iTerm 2');
    iTerm2.activate();
  }
})();
