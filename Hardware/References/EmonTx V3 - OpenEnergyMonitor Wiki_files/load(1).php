var mediaWikiLoadStart=(new Date()).getTime(),mwPerformance=(window.performance&&performance.mark)?performance:{mark:function(){}};mwPerformance.mark('mwLoadStart');function isCompatible(ua){if(ua===undefined){ua=navigator.userAgent;}return!((ua.indexOf('MSIE')!==-1&&parseFloat(ua.split('MSIE')[1])<8)||(ua.indexOf('Firefox/')!==-1&&parseFloat(ua.split('Firefox/')[1])<3)||(ua.indexOf('Opera/')!==-1&&(ua.indexOf('Version/')===-1?parseFloat(ua.split('Opera/')[1])<10:parseFloat(ua.split('Version/')[1])<12))||(ua.indexOf('Opera ')!==-1&&parseFloat(ua.split(' Opera ')[1])<10)||ua.match(/BlackBerry[^\/]*\/[1-5]\./)||ua.match(/webOS\/1\.[0-4]/)||ua.match(/PlayStation/i)||ua.match(/SymbianOS|Series60/)||ua.match(/NetFront/)||ua.match(/Opera Mini/)||ua.match(/S40OviBrowser/)||ua.match(/MeeGo/)||(ua.match(/Glass/)&&ua.match(/Android/)));}(function(){if(!isCompatible()){document.documentElement.className=document.documentElement.className.replace(/(^|\s)client-js(\s|$)/,'$1client-nojs$2');return;}
function startUp(){mw.config=new mw.Map(true);mw.loader.addSource({"local":"/load.php"});mw.loader.register([["site","EAg9QOwG"],["noscript","C5uJHn5I",[],"noscript"],["filepage","N2Dkjes2"],["user.groups","iuWIm6HE",[],"user"],["user","dL0t4ZUc",[],"user"],["user.cssprefs","64Nx0RWw",[],"private"],["user.defaults","u+9GLgQG"],["user.options","+UOu/hSH",[6],"private"],["user.tokens","nefTQe9s",[],"private"],["mediawiki.language.data","e5mNAXXS",[168]],["mediawiki.skinning.elements","iUbUCNZN"],["mediawiki.skinning.content","TG/TKBbc"],["mediawiki.skinning.interface","An/X2e7j"],["mediawiki.skinning.content.parsoid","+EDWYfP0"],["mediawiki.skinning.content.externallinks","SuiX5Nae"],["jquery.accessKeyLabel","BYiIPmJi",[25,129]],["jquery.appear","ihEf3uUQ"],["jquery.arrowSteps","8JLPnuzP"],["jquery.async","WylvoU9B"],["jquery.autoEllipsis","1qIDQ2Dr",[37]],["jquery.badge","dexvaig4",[165]],["jquery.byteLength","tym/CPiA"],["jquery.byteLimit","kZHcjWVF",[21]],["jquery.checkboxShiftClick",
"uK0Ry9Va"],["jquery.chosen","L4g5TjIR"],["jquery.client","YS3aTyM1"],["jquery.color","alCwDxpQ",[27]],["jquery.colorUtil","tpptjaHv"],["jquery.confirmable","iVMyHg/w",[169]],["jquery.cookie","vzQPqLMX"],["jquery.expandableField","rL54C4QF"],["jquery.farbtastic","Sc7XreX1",[27]],["jquery.footHovzer","5lklcQSL"],["jquery.form","EytwtnTr"],["jquery.fullscreen","fpGybiJN"],["jquery.getAttrs","XQcyvj0t"],["jquery.hidpi","wll8uPzA"],["jquery.highlightText","VSaCnnX9",[227,129]],["jquery.hoverIntent","LzOYUBfc"],["jquery.i18n","lnZS2Bbw",[167]],["jquery.localize","9+lwTN5u"],["jquery.makeCollapsible","zv3mYWhO"],["jquery.mockjax","SkBaLJwM"],["jquery.mw-jump","x6wiuzM/"],["jquery.mwExtension","HkUYbcE6"],["jquery.placeholder","0Qd0f7HU"],["jquery.qunit","SIr7s5m/"],["jquery.qunit.completenessTest","Oou8aUsB",[46]],["jquery.spinner","ATsObdsp"],["jquery.jStorage","BgaqYIXe",[93]],["jquery.suggestions","LpSfqdA1",[37]],["jquery.tabIndex","uuI3hqyp"],["jquery.tablesorter","AvxjoHRJ",[227,129,
170]],["jquery.textSelection","3un+epmC",[25]],["jquery.throttle-debounce","8kZLgQEQ"],["jquery.validate","ace4U3Ca"],["jquery.xmldom","wf5aR+OE"],["jquery.tipsy","RY+TUWEN"],["jquery.ui.core","FU/2DP2U",[59],"jquery.ui"],["jquery.ui.core.styles","urb/VMte",[],"jquery.ui"],["jquery.ui.accordion","CrnMN+UW",[58,78],"jquery.ui"],["jquery.ui.autocomplete","oHd3jkX3",[67],"jquery.ui"],["jquery.ui.button","uK8tAIA/",[58,78],"jquery.ui"],["jquery.ui.datepicker","H0SCvGz5",[58],"jquery.ui"],["jquery.ui.dialog","rYqcX2NJ",[62,65,69,71],"jquery.ui"],["jquery.ui.draggable","tQzBnpAZ",[58,68],"jquery.ui"],["jquery.ui.droppable","vcc4kN8B",[65],"jquery.ui"],["jquery.ui.menu","HU4YDreU",[58,69,78],"jquery.ui"],["jquery.ui.mouse","vfU5uCQ/",[78],"jquery.ui"],["jquery.ui.position","wyaRzGIC",[],"jquery.ui"],["jquery.ui.progressbar","4a7u0Pk5",[58,78],"jquery.ui"],["jquery.ui.resizable","2lWcZh8O",[58,68],"jquery.ui"],["jquery.ui.selectable","IfYLwHZ3",[58,68],"jquery.ui"],["jquery.ui.slider",
"Qn3V4b+F",[58,68],"jquery.ui"],["jquery.ui.sortable","Apz9QWsw",[58,68],"jquery.ui"],["jquery.ui.spinner","xAri+wMp",[62],"jquery.ui"],["jquery.ui.tabs","3MEZO4vT",[58,78],"jquery.ui"],["jquery.ui.tooltip","aoj7c54U",[58,69,78],"jquery.ui"],["jquery.ui.widget","+liF7VNk",[],"jquery.ui"],["jquery.effects.core","H+ix9i/W",[],"jquery.ui"],["jquery.effects.blind","YiFkR7sq",[79],"jquery.ui"],["jquery.effects.bounce","d7sUWZxy",[79],"jquery.ui"],["jquery.effects.clip","bf7GkLAt",[79],"jquery.ui"],["jquery.effects.drop","Tk2kATzU",[79],"jquery.ui"],["jquery.effects.explode","Hvlao41/",[79],"jquery.ui"],["jquery.effects.fade","/jvYrvRB",[79],"jquery.ui"],["jquery.effects.fold","cIeAjIKy",[79],"jquery.ui"],["jquery.effects.highlight","ba1VcU34",[79],"jquery.ui"],["jquery.effects.pulsate","GnjfS+Ty",[79],"jquery.ui"],["jquery.effects.scale","vQyCyOuc",[79],"jquery.ui"],["jquery.effects.shake","CSEEJDe6",[79],"jquery.ui"],["jquery.effects.slide","bsdi/KbP",[79],"jquery.ui"],[
"jquery.effects.transfer","bqXgzjaL",[79],"jquery.ui"],["json","LDfWr5aV",[],null,null,"return!!(window.JSON\u0026\u0026JSON.stringify\u0026\u0026JSON.parse);"],["moment","g+LxL7lI"],["mediawiki.apihelp","mZHqA5CX",[119]],["mediawiki.template","VZXFmeWE"],["mediawiki.template.mustache","7GE3bBj3",[96]],["mediawiki.template.regexp","0os6ehak",[96]],["mediawiki.apipretty","Gy1Nq0ec"],["mediawiki.api","Zbd/pfjg",[145,8]],["mediawiki.api.category","WGrK4wNF",[134,100]],["mediawiki.api.edit","4H+prEah",[134,100]],["mediawiki.api.login","vaP9lVTz",[100]],["mediawiki.api.options","qmY1cC6d",[100]],["mediawiki.api.parse","oj+Hsz3K",[100]],["mediawiki.api.upload","w/fdz5II",[227,93,102]],["mediawiki.api.watch","XnH+l20j",[100]],["mediawiki.content.json","IIus0YMF"],["mediawiki.confirmCloseWindow","UsO3n7k3"],["mediawiki.debug","TdV9cU4A",[32,57]],["mediawiki.debug.init","ngZBVBLq",[110]],["mediawiki.feedback","KJLftcWO",[134,125,229]],["mediawiki.feedlink","haYhuJxn"],["mediawiki.filewarning",
"aHHI4KZ0",[229]],["mediawiki.ForeignApi","IxhYISjK",[116]],["mediawiki.ForeignApi.core","rKcY5iKs",[100,228]],["mediawiki.helplink","jnMnofaz"],["mediawiki.hidpi","YHUE4YrE",[36],null,null,"return'srcset'in new Image();"],["mediawiki.hlist","/gLd/Nnd",[25]],["mediawiki.htmlform","QfwjHvlW",[22,129]],["mediawiki.htmlform.styles","AF6FUmG2"],["mediawiki.htmlform.ooui.styles","5NeyNq2+"],["mediawiki.icon","NhbW9nhX"],["mediawiki.inspect","KIfXVmLv",[21,93,129]],["mediawiki.messagePoster","No1Dofp8",[100,228]],["mediawiki.messagePoster.wikitext","emf1Rc2w",[102,125]],["mediawiki.notification","yQiNH2tJ",[177]],["mediawiki.notify","a5RnLAc4"],["mediawiki.RegExp","DXHImJYN"],["mediawiki.pager.tablePager","TeWBKdXY"],["mediawiki.searchSuggest","E1CB8PL7",[35,45,50,100]],["mediawiki.sectionAnchor","Mot2/ONK"],["mediawiki.storage","z1uAPWA3"],["mediawiki.Title","NrLAzKbW",[21,145]],["mediawiki.Upload","l8a8fyUr",[106]],["mediawiki.ForeignUpload","t3ApYMxg",[115,135]],[
"mediawiki.ForeignStructuredUpload","x3JFMHUE",[136]],["mediawiki.Upload.Dialog","MrpKFQku",[139]],["mediawiki.Upload.BookletLayout","AyNAXMMh",[135,169,229]],["mediawiki.ForeignStructuredUpload.BookletLayout","96IGHyvt",[137,139,224,223]],["mediawiki.toc","3qKeYXu1",[146]],["mediawiki.Uri","dUsn9Fnj",[145,98]],["mediawiki.user","9FZg1c8z",[100,146,7]],["mediawiki.userSuggest","yyMAzDDE",[50,100]],["mediawiki.util","ext3GgBz",[15,128]],["mediawiki.cookie","C44b6prk",[29]],["mediawiki.toolbar","5RsVMdEi"],["mediawiki.experiments","VeHMFU0W"],["mediawiki.action.edit","dAfQWN/U",[22,53,150]],["mediawiki.action.edit.styles","Mzj8xwGt"],["mediawiki.action.edit.collapsibleFooter","ZfT6qi8N",[41,146,123]],["mediawiki.action.edit.preview","ImhZZjVF",[33,48,53,155,100,169]],["mediawiki.action.edit.stash","UtA+NSOm",[35,100]],["mediawiki.action.history","0LxTccK4"],["mediawiki.action.history.diff","2Bql8Uc+"],["mediawiki.action.view.dblClickEdit","gWgc0rFL",[177,7]],[
"mediawiki.action.view.metadata","iXRgsDSH"],["mediawiki.action.view.categoryPage.styles","At15bam0"],["mediawiki.action.view.postEdit","6k8/ycLR",[146,169,96]],["mediawiki.action.view.redirect","jsr/Fdgr",[25]],["mediawiki.action.view.redirectPage","szscsseS"],["mediawiki.action.view.rightClickEdit","HqnQT9Pi"],["mediawiki.action.edit.editWarning","lLghZN+P",[53,109,169]],["mediawiki.action.view.filepage","a17vXfGj"],["mediawiki.language","Y+Vky6PR",[166,9]],["mediawiki.cldr","r7YxZgIW",[167]],["mediawiki.libs.pluralruleparser","zbgsj0zq"],["mediawiki.language.init","pT8Gcpgf"],["mediawiki.jqueryMsg","EjtXgyaf",[227,165,145,7]],["mediawiki.language.months","NFmNA8pM",[165]],["mediawiki.language.names","dSrl/DKV",[168]],["mediawiki.language.specialCharacters","lfy9K43n",[165]],["mediawiki.libs.jpegmeta","O0DimprY"],["mediawiki.page.gallery","jFhiXukm",[54,175]],["mediawiki.page.gallery.styles","vT3pT5Gt"],["mediawiki.page.ready","vZ3eYF+g",[15,23,41,43,45]],["mediawiki.page.startup",
"jSis1zGj",[145]],["mediawiki.page.patrol.ajax","74BZfjgR",[48,134,100,177]],["mediawiki.page.watch.ajax","QP4exell",[107,177]],["mediawiki.page.image.pagination","psgNeaTf",[48,142]],["mediawiki.special","EtuR0cxO"],["mediawiki.special.block","TlYl78wE",[145]],["mediawiki.special.changeemail","QNvsGEMk",[145]],["mediawiki.special.changeslist","jpgDNUHu"],["mediawiki.special.changeslist.legend","mwHYJxtF"],["mediawiki.special.changeslist.legend.js","Pr7PsMKn",[41,146]],["mediawiki.special.changeslist.enhanced","qkYgMstg"],["mediawiki.special.edittags","4aNhfRmV",[24]],["mediawiki.special.edittags.styles","Yy4LArYI"],["mediawiki.special.import","w9LNCzMd"],["mediawiki.special.movePage","l8DgtyEx",[221]],["mediawiki.special.movePage.styles","l+84fKKT"],["mediawiki.special.pageLanguage","VxAnTFW2"],["mediawiki.special.pagesWithProp","hXnMPTE6"],["mediawiki.special.preferences","RlLMvTFL",[109,165,127]],["mediawiki.special.recentchanges","4fP/P1wC",[181]],["mediawiki.special.search",
"v2MGy8Lq"],["mediawiki.special.undelete","mq7Sto6Y"],["mediawiki.special.upload","rH5XXAFF",[48,134,100,109,169,173,96]],["mediawiki.special.userlogin.common.styles","TdjqPLkx"],["mediawiki.special.userlogin.signup.styles","jyj76Hn9"],["mediawiki.special.userlogin.login.styles","bSPnJcQy"],["mediawiki.special.userlogin.signup.js","Xdcpcha5",[54,100,169]],["mediawiki.special.unwatchedPages","jwYSQ/gV",[134,107]],["mediawiki.special.javaScriptTest","Q1dHCwWN",[142]],["mediawiki.special.version","l4UI5Wrx"],["mediawiki.legacy.config","G/53ukd0"],["mediawiki.legacy.commonPrint","NKHCQRBo"],["mediawiki.legacy.protect","Mc2VpNzd",[22]],["mediawiki.legacy.shared","ILyWQz2b"],["mediawiki.legacy.oldshared","0FQsruCR"],["mediawiki.legacy.wikibits","P8GPoC6R",[145]],["mediawiki.ui","z5qHrQ88"],["mediawiki.ui.checkbox","sxiFBfaH"],["mediawiki.ui.radio","NLroSu5c"],["mediawiki.ui.anchor","ZXvxrBKZ"],["mediawiki.ui.button","A2zt1r4Q"],["mediawiki.ui.input","QNhZGW7F"],["mediawiki.ui.icon",
"dE9Nv1IK"],["mediawiki.ui.text","FqfUVyuR"],["mediawiki.widgets","dnzeDLaF",[19,22,115,134,224,222]],["mediawiki.widgets.styles","gKJlLP8Z"],["mediawiki.widgets.DateInputWidget","Hvj+O5Qp",[94,229]],["mediawiki.widgets.CategorySelector","5tU1ATu2",[100,229]],["mediawiki.widgets.UserInputWidget","Nhe+K8Xc",[229]],["es5-shim","1cjRpvZv",[],null,null,"return(function(){'use strict';return!this\u0026\u0026!!Function.prototype.bind;}());"],["dom-level2-shim","/ibwRjFv",[],null,null,"return!!window.Node;"],["oojs","8WnjF86H",[226,93]],["oojs-ui","+dEaly9c",[228,230,231,232,233]],["oojs-ui.styles","R3Xm0Vkh"],["oojs-ui.styles.icons","5d5ojU5m"],["oojs-ui.styles.indicators","vLaADRGG"],["oojs-ui.styles.textures","90f/iNC+"],["oojs-ui.styles.icons-accessibility","Gyf+qom9"],["oojs-ui.styles.icons-alerts","aRd/qaJw"],["oojs-ui.styles.icons-content","S+dh7Glm"],["oojs-ui.styles.icons-editing-advanced","MVSXBOMh"],["oojs-ui.styles.icons-editing-core","fWSod+t2"],[
"oojs-ui.styles.icons-editing-list","JNV81HOh"],["oojs-ui.styles.icons-editing-styling","a9+fh49o"],["oojs-ui.styles.icons-interactions","kAfXIO0V"],["oojs-ui.styles.icons-layout","3OHWVsPL"],["oojs-ui.styles.icons-location","5KlZj+q3"],["oojs-ui.styles.icons-media","kykuBpIP"],["oojs-ui.styles.icons-moderation","EOUZATrF"],["oojs-ui.styles.icons-movement","bwrrw7mY"],["oojs-ui.styles.icons-user","ikjAlavi"],["oojs-ui.styles.icons-wikimedia","h+qJtZZt"],["ext.pygments","jNfhbR6a"],["ext.geshi.visualEditor","oZSb+9N5",["ext.visualEditor.mwcore"]],["ext.nuke","PI6aCH5o"],["skins.vector.styles","eg4/a9Ey"],["skins.vector.styles.responsive","l3FEdPBX"],["skins.vector.js","JByjJddQ",[51,54]],["ext.embedVideo","bKNJ8qJ3"],["ext.confirmAccount","7ckSAMHO"]]);;mw.config.set({"wgLoadScript":"/load.php","debug":!1,"skin":"vector","stylepath":"/skins","wgUrlProtocols":
"bitcoin\\:|ftp\\:\\/\\/|ftps\\:\\/\\/|geo\\:|git\\:\\/\\/|gopher\\:\\/\\/|http\\:\\/\\/|https\\:\\/\\/|irc\\:\\/\\/|ircs\\:\\/\\/|magnet\\:|mailto\\:|mms\\:\\/\\/|news\\:|nntp\\:\\/\\/|redis\\:\\/\\/|sftp\\:\\/\\/|sip\\:|sips\\:|sms\\:|ssh\\:\\/\\/|svn\\:\\/\\/|tel\\:|telnet\\:\\/\\/|urn\\:|worldwind\\:\\/\\/|xmpp\\:|\\/\\/","wgArticlePath":"/index.php/$1","wgScriptPath":"","wgScriptExtension":".php","wgScript":"/index.php","wgSearchType":null,"wgVariantArticlePath":!1,"wgActionPaths":{},"wgServer":"https://wiki.openenergymonitor.org","wgServerName":"wiki.openenergymonitor.org","wgUserLanguage":"en-gb","wgContentLanguage":"en-gb","wgTranslateNumerals":!0,"wgVersion":"1.26.2","wgEnableAPI":!0,"wgEnableWriteAPI":!0,"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"OpenEnergyMonitor Wiki","5":"OpenEnergyMonitor Wiki talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":
"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"openenergymonitor wiki":4,"openenergymonitor_wiki_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"image":6,"image_talk":7,"project":4,"project_talk":5},"wgContentNamespaces":[0],"wgSiteName":"OpenEnergyMonitor Wiki","wgDBname":"wiki","wgExtraSignatureNamespaces":[],"wgAvailableSkins":{"vector":"Vector","fallback":"Fallback","apioutput":"ApiOutput"},"wgExtensionAssetsPath":"/extensions","wgCookiePrefix":"wiki","wgCookieDomain":"openenergymonitor.org","wgCookiePath":"/","wgCookieExpiration":15552000,"wgResourceLoaderMaxQueryLength":-1,"wgCaseSensitiveNamespaces":[],"wgLegalTitleChars":" %!\"$&'()*,\\-./0-9:;=?@A-Z\\\\\\^_`a-z~+\\u0080-\\uFFFF","wgResourceLoaderStorageVersion":1,
"wgResourceLoaderStorageEnabled":!1,"wgResourceLoaderLegacyModules":["mediawiki.legacy.wikibits"],"wgForeignUploadTargets":[],"wgEnableUploads":!0});window.RLQ=window.RLQ||[];while(RLQ.length){RLQ.shift()();}window.RLQ={push:function(fn){fn();}};}var script=document.createElement('script');script.src="/load.php?debug=false&lang=en-gb&modules=jquery%2Cmediawiki&only=scripts&skin=vector&version=Si%2B5pRik";script.onload=script.onreadystatechange=function(){if(!script.readyState||/loaded|complete/.test(script.readyState)){script.onload=script.onreadystatechange=null;script=null;startUp();}};document.getElementsByTagName('head')[0].appendChild(script);}());