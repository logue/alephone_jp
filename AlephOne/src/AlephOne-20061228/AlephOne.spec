%define name AlephOne
%define version 20061228
%define release 1

Summary: 3D first-person shooter game
Name: %{name}
Version: %{version}
Release: %{release}
License: GPL
Group: Amusements/Games
Source: %{name}-%{version}.tar.gz
URL: http://alephone.cebix.net
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
# not relocatable because the data file packages depend upon the location
# of the data files in this package

Requires: AlephOne-core-data
Requires: SDL >= 1.2.0 SDL_image >= 1.2.0 SDL_net lua speex
BuildRequires: SDL-devel SDL_image-devel SDL_net-devel speex-devel

%description
Aleph One is an Open Source 3D first-person shooter game, based on the game
Marathon 2 by Bungie Software. It is set in a Sci-Fi universe dominated by
deviant computer AIs and features a well thought-out plot. Aleph One
supports, but doesn't require, OpenGL for rendering.

This package requires additional data -- shape, sound, and map information
-- in order to be installed. One possible source of this core data is the
AlephOne-minf-demo package.

%prep
%setup -q

%build
%configure
make

%install
rm -rf ${RPM_BUILD_ROOT}
%makeinstall

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%doc AUTHORS COPYING INSTALL.Unix README docs/MML.html docs/Cheat_Codes
%{_bindir}/alephone
%{_datadir}/AlephOne/Fonts
%{_datadir}/AlephOne/MML
%{_datadir}/AlephOne/Themes/Default

%changelog
* Sun Nov 20 2005 Christian Bauer <www.cebix.net>
- modernized the spec file a bit

* Thu Oct  5 2000 Christian Bauer <Christian.Bauer@uni-mainz.de>
- Added docs and theme data files
- Package name and version are set by configure script

* Fri Sep 30 2000 Tom Moertel <tom-rpms-alephone@moertel.com>
- Added a requirement to the base package for AlephOne-core-data
- Split out the Marathon Infinity Demo data into its own package

* Thu Sep 29 2000 Tom Moertel <tom-rpms-alephone@moertel.com>
- Added patch for SDL 1.1.5 SDL_SetClipping incompatability.

* Sat Sep 23 2000 Tom Moertel <tom-rpms-alephone@moertel.com>
- Added Marathon Infinity Demo data to package.
