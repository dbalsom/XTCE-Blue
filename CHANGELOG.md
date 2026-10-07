# Changelog

## [0.2.0] - 2026-10-06

### Added

- Added headless `--benchmark` mode. Runs to BIOS `INT 19h` and prints performance stats.
- Added software interrupt breakpoints and instruction counting.
- Added CPU speed, CGA refresh rate, and utilization in the window title.
- Added more CGA/CRTC diagnostics in the video status window.
- Updated to GLaBIOS 0.4

### Changed

- Windows builds no longer open a console window when launched from Explorer.
- Disabled unused SDL_mixer decoders.
- Increased PC speaker volume.
- Capped presentation at 240 FPS to reduce CPU/GPU load.
- Decoupled CPU timing from rendering and audio. Fixed pause/reset timing and catch-up after stalls.
- Improved PC speaker audio quality and buffering. Added clock drift handling.
- Renderer now skips display texture uploads when nothing changed.
- Simplified microcode loading. Removed startup debug microcode-decoding spam.
- Simplified `DAA` and `DAS` instructions.

### Fixed

- `DAA` now uses `AL` and sets flags correctly.
- Corrected CGA tick rate, display aperture, and added CGA RAM mirror in 32K aperture.
- Fixed CGA cursor rendering and text/cursor blink timing.
- Brought CRTC behavior in line with MartyPC. Area 5150's lake effect works now. Still some glitches.
- Fixed keyboard clear/acknowledgement timing and IRQ1 handling.
- Fixed PIT mode 0 reloads.
- Fixed FDC busy flag during DMA result reads (thanks peterc)
- Implemented headless startup and shutdown without audio or GUI state.

### Testing

- SSTs now use the initial prefetch queue and stop on the next instruction's first-byte queue status.
- SSTs now feed NOPs for later prefetches.
- Fixed SST register/flag masks
- Added IP, cycle timing, bus status, and queue status checks.
- Improved per-file summaries and test failure details. Test runner returns a nonzero exit code on test failure
- All 3,007,000 tests in the 8088 V2 suite now pass, including timing and bus status checks.

## 0.1.0

- Initial release.

[0.2.0]: https://github.com/dbalsom/XTCE-Blue/pull/4
