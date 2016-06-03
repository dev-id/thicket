Release Notes
=============

Release 0.16-alpha:
-------------------

Server sends user login/logout updates to clients, client shows current
users in server window.

Client MTGJSON AllSets update dialog now uses a combobox to display
builtin URL's in addition to others used to successfully download a valid
file.

Consolidated hostname and port in client connect dialog.

Updated client quit behavior to confirm exit when there are unsaved
changes.

Added a "Quit" menu item.

Fix #1: Clear server chat messages in client on disconnect

Other changes:
- Added unit test to create every card in every set


Release 0.15-alpha:
-------------------

Added an area to the client's server view to show server announcements.

Server alerts now bring up a modeless dialog on client.

Client saves and restores window size and position, as well as settings
for each pane (zoom, categoriztion, sort).

Other client changes:
- Rearranged menus
- Improved download progress feedback for MTG JSON file
- Updated about and compatibility dialog
- Limit chat histories to 1000 messages

Release 0.14-alpha:
-------------------

Introduced client dialog for downloading AllSets.json card data file.

Modified client default setting for server name to 'thicketdraft.net'.

Changed client save dialog to not use native widget.
  - On Windows the native dialog would interfere with the program event
    loop, resulting in keepalives not being sent, resulting in server
    disconnections.

Release 0.13-alpha:
-------------------

Fix for being unable to draft split cards.

Added server connection monitoring with client keepalive messages.
  - Previously, if a client vanished, the server would not know about it
    and keep its client connection open.

Other changes:
- Removed extraneous pack generation in server
- Improved unit test coverage for cardpools and mtgjson
- Code reorganization
- Client state machine refactoring

Release 0.12-alpha:
-------------------

First public release.