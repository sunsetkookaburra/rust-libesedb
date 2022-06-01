Name: libesedb
Version: 20210424
Release: 1
Summary: Library to access the Extensible Storage Engine (ESE) Database File (EDB) format
Group: System Environment/Libraries
License: LGPLv3+
Source: %{name}-%{version}.tar.gz
URL: https://github.com/libyal/libesedb
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
                
BuildRequires: gcc                

%description -n libesedb
Library to access the Extensible Storage Engine (ESE) Database File (EDB) format

%package -n libesedb-static
Summary: Library to access the Extensible Storage Engine (ESE) Database File (EDB) format
Group: Development/Libraries
Requires: libesedb = %{version}-%{release}

%description -n libesedb-static
Static library version of libesedb.

%package -n libesedb-devel
Summary: Header files and libraries for developing applications for libesedb
Group: Development/Libraries
Requires: libesedb = %{version}-%{release}

%description -n libesedb-devel
Header files and libraries for developing applications for libesedb.

%package -n libesedb-python2
Obsoletes: libesedb-python < %{version}
Provides: libesedb-python = %{version}
Summary: Python 2 bindings for libesedb
Group: System Environment/Libraries
Requires: libesedb = %{version}-%{release} python2
BuildRequires: python2-devel

%description -n libesedb-python2
Python 2 bindings for libesedb

%package -n libesedb-python3
Summary: Python 3 bindings for libesedb
Group: System Environment/Libraries
Requires: libesedb = %{version}-%{release} python3
BuildRequires: python3-devel

%description -n libesedb-python3
Python 3 bindings for libesedb

%package -n libesedb-tools
Summary: Several tools for reading Extensible Storage Engine (ESE) Database Files (EDB)
Group: Applications/System
Requires: libesedb = %{version}-%{release}  
  

%description -n libesedb-tools
Several tools for reading Extensible Storage Engine (ESE) Database Files (EDB)

%prep
%setup -q

%build
%configure --prefix=/usr --libdir=%{_libdir} --mandir=%{_mandir} --enable-python2 --enable-python3
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files -n libesedb
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%attr(755,root,root) %{_libdir}/*.so.*

%files -n libesedb-static
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%attr(755,root,root) %{_libdir}/*.a

%files -n libesedb-devel
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/libesedb.pc
%{_includedir}/*
%{_mandir}/man3/*

%files -n libesedb-python2
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/python2*/site-packages/*.a
%{_libdir}/python2*/site-packages/*.la
%{_libdir}/python2*/site-packages/*.so

%files -n libesedb-python3
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/python3*/site-packages/*.a
%{_libdir}/python3*/site-packages/*.la
%{_libdir}/python3*/site-packages/*.so

%files -n libesedb-tools
%defattr(644,root,root,755)
%license COPYING COPYING.LESSER
%doc AUTHORS README
%attr(755,root,root) %{_bindir}/*
%{_mandir}/man1/*

%changelog
* Sat Apr 24 2021 Joachim Metz <joachim.metz@gmail.com> 20210424-1
- Auto-generated

