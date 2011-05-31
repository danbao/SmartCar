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
				<Property Name="Source[0].itemID" Type="Str">{3FC4744B-3329-4C47-9E01-E62F6D875A87}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/lz.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
			</Item>
			<Item Name="嘉庚谷风智能车专用调试软件" Type="Installer">
				<Property Name="AutoIncrement" Type="Bool">true</Property>
				<Property Name="BuildLabel" Type="Str">嘉庚谷风智能车专用调试软件</Property>
				<Property Name="BuildLocation" Type="Path">../../Builds/v2/嘉庚谷风智能车专用调试软件</Property>
				<Property Name="DirInfo.Count" Type="Int">1</Property>
				<Property Name="DirInfo.DefaultDir" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="DirInfo[0].DirName" Type="Str">嘉庚谷风</Property>
				<Property Name="DirInfo[0].DirTag" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="DirInfo[0].ParentTag" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="DistID" Type="Str">{7CDC7A33-D7A0-41B2-9009-5F1EC64E0569}</Property>
				<Property Name="DistParts.Count" Type="Int">1</Property>
				<Property Name="DistPartsInfo[0].FlavorID" Type="Str">DefaultFull</Property>
				<Property Name="DistPartsInfo[0].ProductID" Type="Str">{2CA542BC-E002-4064-84DB-49B3E558A26D}</Property>
				<Property Name="DistPartsInfo[0].ProductName" Type="Str">LabVIEW运行引擎8.6</Property>
				<Property Name="DistPartsInfo[0].UpgradeCode" Type="Str">{7975A1CC-5DCA-4997-EE8C-C1903BA18512}</Property>
				<Property Name="FileInfo.Count" Type="Int">3</Property>
				<Property Name="FileInfo[0].DirTag" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="FileInfo[0].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.exe</Property>
				<Property Name="FileInfo[0].FileTag" Type="Str">{C813BD4B-ABDC-441B-A414-1E288D965FA0}</Property>
				<Property Name="FileInfo[0].Type" Type="Int">3</Property>
				<Property Name="FileInfo[0].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="FileInfo[1].DirTag" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="FileInfo[1].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.aliases</Property>
				<Property Name="FileInfo[1].FileTag" Type="Str">{AB294EBB-DDA3-4D18-9E8B-8329A8ED50DB}</Property>
				<Property Name="FileInfo[1].Type" Type="Int">3</Property>
				<Property Name="FileInfo[1].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="FileInfo[2].DirTag" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="FileInfo[2].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.ini</Property>
				<Property Name="FileInfo[2].FileTag" Type="Str">{499E48B5-0610-4E54-BDDB-6FC56DFE24E4}</Property>
				<Property Name="FileInfo[2].Type" Type="Int">3</Property>
				<Property Name="FileInfo[2].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="InstSpecVersion" Type="Str">8608001</Property>
				<Property Name="Language" Type="Int">2052</Property>
				<Property Name="LicenseFile" Type="Ref"></Property>
				<Property Name="OSCheck" Type="Int">0</Property>
				<Property Name="OSCheck_Vista" Type="Bool">false</Property>
				<Property Name="ProductName" Type="Str">v2</Property>
				<Property Name="ProductVersion" Type="Str">1.0.1</Property>
				<Property Name="ReadmeFile" Type="Ref"></Property>
				<Property Name="ShortcutInfo.Count" Type="Int">1</Property>
				<Property Name="ShortcutInfo[0].DirTag" Type="Str">{B9E310F1-839C-48B7-8CAE-33000780C26E}</Property>
				<Property Name="ShortcutInfo[0].FileTag" Type="Str">{C813BD4B-ABDC-441B-A414-1E288D965FA0}</Property>
				<Property Name="ShortcutInfo[0].FileTagDir" Type="Str">{A8F64DCD-EB75-4739-8591-8F72E297766F}</Property>
				<Property Name="ShortcutInfo[0].Name" Type="Str">厦大嘉庚谷风-专用调试软件</Property>
				<Property Name="ShortcutInfo[0].SubDir" Type="Str">v2</Property>
				<Property Name="UpgradeCode" Type="Str">{7C7FE978-D505-4898-9F5E-F9326C5229FA}</Property>
			</Item>
		</Item>
	</Item>
</Project>
