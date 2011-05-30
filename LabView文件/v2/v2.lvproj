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
		<Item Name="lz.vi" Type="VI" URL="../lz.vi"/>
		<Item Name="large.ico" Type="Document" URL="../ico/large.ico"/>
		<Item Name="依赖关系" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
			<Item Name="visarc" Type="Document" URL="../../../../../../Program Files/National Instruments/LabVIEW 8.6/resource/visarc"/>
		</Item>
		<Item Name="程序生成规范" Type="Build">
			<Item Name="嘉庚谷风-调试软件" Type="EXE">
				<Property Name="App_applicationGUID" Type="Str">{C813BD4B-ABDC-441B-A414-1E288D965FA0}</Property>
				<Property Name="App_applicationName" Type="Str">厦大嘉庚谷风-专用调试软件.exe</Property>
				<Property Name="App_fileDescription" Type="Str">嘉庚谷风-调试软件</Property>
				<Property Name="App_fileVersion.major" Type="Int">2</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{AB294EBB-DDA3-4D18-9E8B-8329A8ED50DB}</Property>
				<Property Name="App_INI_GUID" Type="Str">{499E48B5-0610-4E54-BDDB-6FC56DFE24E4}</Property>
				<Property Name="App_internalName" Type="Str">谷风-beta2</Property>
				<Property Name="App_legalCopyright" Type="Str">版权 2011 by 林震</Property>
				<Property Name="App_productName" Type="Str">厦大嘉庚谷风光电专用调试软件-beta2</Property>
				<Property Name="Bld_buildSpecName" Type="Str">嘉庚谷风-调试软件</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">ChineseS</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Destination[0].destName" Type="Str">厦大嘉庚谷风-专用调试软件.exe</Property>
				<Property Name="Destination[0].path" Type="Path">/D/Documents/SmartCar/trunk/调试软件/internal.llb</Property>
				<Property Name="Destination[0].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">支持目录</Property>
				<Property Name="Destination[1].path" Type="Path">/D/Documents/SmartCar/trunk/调试软件/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/我的电脑/large.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{26FE3CC4-3ED5-4780-A5DC-39943C4F97AB}</Property>
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
