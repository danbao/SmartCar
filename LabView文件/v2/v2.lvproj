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
				<Property Name="App_autoIncrement" Type="Bool">true</Property>
				<Property Name="App_fileDescription" Type="Str">嘉庚谷风-调试软件</Property>
				<Property Name="App_fileVersion.build" Type="Int">1</Property>
				<Property Name="App_fileVersion.major" Type="Int">2</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{AB294EBB-DDA3-4D18-9E8B-8329A8ED50DB}</Property>
				<Property Name="App_INI_GUID" Type="Str">{499E48B5-0610-4E54-BDDB-6FC56DFE24E4}</Property>
				<Property Name="App_internalName" Type="Str">谷风-beta3</Property>
				<Property Name="App_legalCopyright" Type="Str">版权 2011 by 林震</Property>
				<Property Name="App_productName" Type="Str">厦大嘉庚谷风光电专用调试软件-beta3</Property>
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
				<Property Name="Source[0].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applyProperties" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applySaveSettings" Type="Bool">true</Property>
				<Property Name="Source[0].destinationIndex" Type="Int">1</Property>
				<Property Name="Source[0].itemID" Type="Str">{498B1E29-0675-42F7-BAC8-B01A73424C23}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/lz.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
			</Item>
			<Item Name="嘉庚谷风智能车-专用调试软件" Type="Installer">
				<Property Name="arpCompany" Type="Str">厦门大学嘉庚学院</Property>
				<Property Name="arpURL" Type="Str">http://www.imlim.com</Property>
				<Property Name="AutoIncrement" Type="Bool">true</Property>
				<Property Name="BuildLabel" Type="Str">嘉庚谷风智能车-专用调试软件</Property>
				<Property Name="BuildLocation" Type="Path">../../../调试软件/嘉庚谷风智能车专用调试软件</Property>
				<Property Name="DirInfo.Count" Type="Int">2</Property>
				<Property Name="DirInfo.DefaultDir" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="DirInfo[0].DirName" Type="Str">嘉庚谷风智能车专用调试软件</Property>
				<Property Name="DirInfo[0].DirTag" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="DirInfo[0].ParentTag" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="DirInfo[1].DirName" Type="Str">data</Property>
				<Property Name="DirInfo[1].DirTag" Type="Str">{AC54737C-07EA-4859-B51A-048C0557BB98}</Property>
				<Property Name="DirInfo[1].ParentTag" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="DistID" Type="Str">{2B1EF9BA-EF05-45A2-A4A1-5E820B9C5831}</Property>
				<Property Name="DistParts.Count" Type="Int">2</Property>
				<Property Name="DistPartsInfo[0].FlavorID" Type="Str">DefaultFull</Property>
				<Property Name="DistPartsInfo[0].ProductID" Type="Str">{2CA542BC-E002-4064-84DB-49B3E558A26D}</Property>
				<Property Name="DistPartsInfo[0].ProductName" Type="Str">LabVIEW运行引擎8.6</Property>
				<Property Name="DistPartsInfo[0].UpgradeCode" Type="Str">{7975A1CC-5DCA-4997-EE8C-C1903BA18512}</Property>
				<Property Name="DistPartsInfo[1].FlavorID" Type="Str">_deployment_</Property>
				<Property Name="DistPartsInfo[1].ProductID" Type="Str">{A9754D6B-7626-4872-83FC-F34B0ECCEC2A}</Property>
				<Property Name="DistPartsInfo[1].ProductName" Type="Str">NI-VISA Runtime 4.0</Property>
				<Property Name="DistPartsInfo[1].UpgradeCode" Type="Str">{8627993A-3F66-483C-A562-0D3BA3F267B1}</Property>
				<Property Name="FileInfo.Count" Type="Int">3</Property>
				<Property Name="FileInfo[0].DirTag" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="FileInfo[0].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.exe</Property>
				<Property Name="FileInfo[0].FileTag" Type="Str">{C813BD4B-ABDC-441B-A414-1E288D965FA0}</Property>
				<Property Name="FileInfo[0].Type" Type="Int">3</Property>
				<Property Name="FileInfo[0].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="FileInfo[1].DirTag" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="FileInfo[1].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.aliases</Property>
				<Property Name="FileInfo[1].FileTag" Type="Str">{AB294EBB-DDA3-4D18-9E8B-8329A8ED50DB}</Property>
				<Property Name="FileInfo[1].Type" Type="Int">3</Property>
				<Property Name="FileInfo[1].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="FileInfo[2].DirTag" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="FileInfo[2].FileName" Type="Str">厦大嘉庚谷风-专用调试软件.ini</Property>
				<Property Name="FileInfo[2].FileTag" Type="Str">{499E48B5-0610-4E54-BDDB-6FC56DFE24E4}</Property>
				<Property Name="FileInfo[2].Type" Type="Int">3</Property>
				<Property Name="FileInfo[2].TypeID" Type="Ref">/我的电脑/程序生成规范/嘉庚谷风-调试软件</Property>
				<Property Name="InstSpecVersion" Type="Str">8608001</Property>
				<Property Name="Language" Type="Int">2052</Property>
				<Property Name="LicenseFile" Type="Ref"></Property>
				<Property Name="OSCheck" Type="Int">0</Property>
				<Property Name="OSCheck_Vista" Type="Bool">false</Property>
				<Property Name="ProductName" Type="Str">嘉庚谷风智能车专用调试软件v2</Property>
				<Property Name="ProductVersion" Type="Str">1.0.1</Property>
				<Property Name="ReadmeFile" Type="Ref"></Property>
				<Property Name="ShortcutInfo.Count" Type="Int">1</Property>
				<Property Name="ShortcutInfo[0].DirTag" Type="Str">{5F651F99-96E4-4E49-AB4B-2AF1DC09E21C}</Property>
				<Property Name="ShortcutInfo[0].FileTag" Type="Str">{C813BD4B-ABDC-441B-A414-1E288D965FA0}</Property>
				<Property Name="ShortcutInfo[0].FileTagDir" Type="Str">{078B6E2F-A2C7-4862-A63C-C5482BBE37CA}</Property>
				<Property Name="ShortcutInfo[0].Name" Type="Str">厦大嘉庚谷风-专用调试软件</Property>
				<Property Name="ShortcutInfo[0].SubDir" Type="Str">嘉庚谷风智能车专用调试软件</Property>
				<Property Name="UpgradeCode" Type="Str">{29BF1DD6-27E5-4FD0-8865-43DD0593276C}</Property>
				<Property Name="WindowMessage" Type="Str">嘉庚谷风智能车专用调试软件 by 林震</Property>
				<Property Name="WindowTitle" Type="Str">嘉庚谷风智能车专用调试软件</Property>
			</Item>
		</Item>
	</Item>
</Project>
