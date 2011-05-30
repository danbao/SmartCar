<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="8608001">
	<Item Name="我的电脑" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="lz.vi" Type="VI" URL="../../lz.vi"/>
		<Item Name="middle.ico" Type="Document" URL="../../../v2/ico/middle.ico"/>
		<Item Name="依赖关系" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
		</Item>
		<Item Name="程序生成规范" Type="Build">
			<Item Name="嘉庚光电谷风队-专用调试软件" Type="EXE">
				<Property Name="App_applicationGUID" Type="Str">{F3EE46C8-0E7F-4A79-89B5-E7715FC4AB0A}</Property>
				<Property Name="App_applicationName" Type="Str">嘉庚谷风.exe</Property>
				<Property Name="App_autoIncrement" Type="Bool">true</Property>
				<Property Name="App_fileDescription" Type="Str">嘉庚光电谷风队-专用调试软件  by 林震</Property>
				<Property Name="App_fileVersion.build" Type="Int">1</Property>
				<Property Name="App_fileVersion.major" Type="Int">1</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{ABD8B25A-C07C-483F-8DEF-4FF5FA49ED3C}</Property>
				<Property Name="App_INI_GUID" Type="Str">{46E568D7-2CB4-42B3-BEF1-3DC0D016C9A2}</Property>
				<Property Name="App_internalName" Type="Str">谷风1号</Property>
				<Property Name="App_legalCopyright" Type="Str">版权 2011 by 林震</Property>
				<Property Name="App_productName" Type="Str">嘉庚光电谷风队-专用调试软件</Property>
				<Property Name="Bld_buildSpecName" Type="Str">嘉庚光电谷风队-专用调试软件</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">ChineseS</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Destination[0].destName" Type="Str">嘉庚谷风.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/嘉庚光电谷风队-专用调试软件/internal.llb</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">支持目录</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/嘉庚光电谷风队-专用调试软件/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/我的电脑/middle.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{7959E76F-0730-4FDF-BF01-41A88F39267D}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/lz.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
			</Item>
		</Item>
	</Item>
</Project>
