Name: libesedb
Version: 20230824
Release: 1
Summary: Library to access the Extensible Storage Engine (ESE) Database File (EDB) format
Group: System Environment/Libraries
License: LGPL-3.0-or-later
Source: %{name}-%{version}.tar.gz
URL: https://github.com/libyal/libesedb
                
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
%configure --prefix=/usr --libdir=%{_libdir} --mandir=%{_mandir} --enable-python3
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files -n libesedb
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/*.so.*

%files -n libesedb-static
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/*.a

%files -n libesedb-devel
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/*.so
%{_libdir}/pkgconfig/libesedb.pc
%{_includedir}/*
%{_mandir}/man3/*

%files -n libesedb-python3
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_libdir}/python3*/site-packages/*.a
%{_libdir}/python3*/site-packages/*.so

%files -n libesedb-tools
%license COPYING COPYING.LESSER
%doc AUTHORS README
%{_bindir}/*
%{_mandir}/man1/*

%changelog
* Sat Sep 30 2023 Joachim Metz <joachim.metz@gmail.com> 20230824-1
- Auto-generated

