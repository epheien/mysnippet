#!/usr/bin/env osascript -l JavaScript

(function() {
  let app = Application.currentApplication();
  app.includeStandardAdditions = true;
  let se = Application('System Events');
  se.keystroke('k', { using: 'command down' }) // Press Cmd-K
})();
