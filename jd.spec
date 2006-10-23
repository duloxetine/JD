##########################################
# For using cvs: do
# cvs -d:pserver:anonymous@cvs.sourceforge.jp:/cvsroot/jd4linux login 
# enter return
# cvs -z3 -d:pserver:anonymous@cvs.sourceforge.jp:/cvsroot/jd4linux co jd
# mv jd jd-%%{main_ver}-%%{strtag}
#
##########################################
# Defined by upsteam
#
%define         main_ver      1.8.0
%define         strtag        beta061023
%define         repoid        21934


# Defined by vendor
#
%define         vendor_rel    1
%define         vendor        fedora
%define         category      X-Fedora
%define         gtkmmdevel    gtkmm24-devel
%define         icondir       %{_datadir}/icons/hicolor/96x96/apps/

# Define this if this is pre-version
%define         pre_release   1

%if %{pre_release}
%define         rel           0.%{vendor_rel}.%{strtag}%{?dist}
%else
%define         rel           %{vendor_rel}%{?dist}
%endif


##########################################

Name:           jd
Version:        %{main_ver}
Release:        %{rel}
Summary:        A 2ch browser

Group:          Applications/Internet
License:        GPL
URL:            http://jd4linux.sourceforge.jp/
Source0:        http://osdn.dl.sourceforge.jp/jd4linux/%{repoid}/%{name}-%{main_ver}-%{strtag}.tgz
#Source0:	%{name}-%{main_ver}-%{strtag}.tgz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  %{gtkmmdevel}
BuildRequires:  libtool automake
BuildRequires:  openssl-devel
BuildRequires:  desktop-file-utils
BuildRequires:  libSM-devel
Requires:       fonts-japanese


%description
JD is a 2ch browser based on gtkmm2.

%prep
%setup -q -n %{name}-%{main_ver}-%{strtag}
find . -name CVS | sort -r | xargs %{__rm} -rf

%build
sh autogen.sh

%configure
%{__make} %{?_smp_mflags}

%install
%{__rm} -rf $RPM_BUILD_ROOT
%{__make} install DESTDIR=$RPM_BUILD_ROOT

%{__mkdir_p} $RPM_BUILD_ROOT%{_datadir}/applications
%{__mkdir_p} $RPM_BUILD_ROOT%{icondir}

%{__install} -p -m 644 %{name}.png $RPM_BUILD_ROOT%{icondir}

desktop-file-install \
   --vendor %{vendor} \
   --dir $RPM_BUILD_ROOT%{_datadir}/applications \
   --add-category %{category} \
   %{name}.desktop

%clean
%{__rm} -rf $RPM_BUILD_ROOT

%post
touch --no-create %{_datadir}/icons/hicolor || :
%{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :

%postun
touch --no-create %{_datadir}/icons/hicolor || :
%{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :

%files
%defattr(-,root,root,-)
%doc COPYING ChangeLog README
%{_bindir}/%{name}
%{_datadir}/applications/%{vendor}-%{name}.desktop
%{icondir}/%{name}.png

%changelog
* Sat Oct  7 2006 Mamoru Tasaka <mtasaka@ioa.s.u-tokyo.ac.jp> - 1.7.0-2
- Add libSM-devel to BuildRequires.

* Wed Sep 27 2006 Mamoru Tasaka <mtasaka@ioa.s.u-tokyo.ac.jp> - 1.7.0-1
- 1.7.0

* Mon Sep 25 2006 Mamoru Tasaka <mtasaka@ioa.s.u-tokyo.ac.jp> - 1.7.0-0.1.rc060921
- Import to Fedora Extras.

* Sun Mar  9 2006 Houritsuchu <houritsuchu@hotmail.com>
- Version up.
- add icon

* Sat Feb 25 2006 Houritsuchu <houritsuchu@hotmail.com>
- first
