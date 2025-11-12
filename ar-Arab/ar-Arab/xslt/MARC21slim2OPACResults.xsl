<?xml version="1.0" encoding="UTF-8"?>
<!-- $Id: MARC21slim2DC.xsl,v 1.1 2003/01/06 08:20:27 adam Exp $ -->
<!DOCTYPE stylesheet>
<xsl:stylesheet version="1.0"
  xmlns:marc="http://www.loc.gov/MARC21/slim"
  xmlns:items="http://www.koha-community.org/items"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:str="http://exslt.org/strings" exclude-result-prefixes="marc items str">
  <xsl:import href="MARC21slimUtils.xsl"/>
  <xsl:output method = "html" indent="yes" omit-xml-declaration = "yes" encoding="UTF-8"/>
  <xsl:key name="item-by-status" match="items:item" use="items:status"/>
  <xsl:key name="item-by-status-and-branch-home" match="items:item" use="concat(items:status, ' ', items:homebranch)"/>
  <xsl:key name="item-by-status-and-branch-holding" match="items:item" use="concat(items:status, ' ', items:holdingbranch)"/>
  <xsl:key name="item-by-substatus-and-branch" match="items:item" use="concat(items:substatus, ' ', items:homebranch)"/>

  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="marc:record">

    <xsl:variable name="itemcount" select="count(items:items/items:item)"/>

    <!-- Option: Display Alternate Graphic Representation (MARC 880) -->
    <xsl:variable name="display880" select="boolean(marc:datafield[@tag=880])"/>

    <xsl:variable name="UseControlNumber" select="marc:sysprefs/marc:syspref[@name='UseControlNumber']"/>
    <xsl:variable name="UseAuthoritiesForTracings" select="marc:sysprefs/marc:syspref[@name='UseAuthoritiesForTracings']"/>
    <xsl:variable name="OPACResultsLibrary" select="marc:sysprefs/marc:syspref[@name='OPACResultsLibrary']"/>
    <xsl:variable name="hidelostitems" select="marc:sysprefs/marc:syspref[@name='hidelostitems']"/>
    <xsl:variable name="DisplayOPACiconsXSLT" select="marc:sysprefs/marc:syspref[@name='DisplayOPACiconsXSLT']"/>
    <xsl:variable name="OPACURLOpenInNewWindow" select="marc:sysprefs/marc:syspref[@name='OPACURLOpenInNewWindow']"/>
    <xsl:variable name="URLLinkText" select="marc:sysprefs/marc:syspref[@name='URLLinkText']"/>
    <xsl:variable name="Show856uAsImage" select="marc:sysprefs/marc:syspref[@name='OPACDisplay856uAsImage']"/>
    <xsl:variable name="AlternateHoldingsField" select="substring(marc:sysprefs/marc:syspref[@name='AlternateHoldingsField'], 1, 3)"/>
    <xsl:variable name="AlternateHoldingsSubfields" select="substring(marc:sysprefs/marc:syspref[@name='AlternateHoldingsField'], 4)"/>
    <xsl:variable name="AlternateHoldingsSeparator" select="marc:sysprefs/marc:syspref[@name='AlternateHoldingsSeparator']"/>
    <xsl:variable name="OPACItemLocation" select="marc:sysprefs/marc:syspref[@name='OPACItemLocation']"/>
    <xsl:variable name="singleBranchMode" select="marc:sysprefs/marc:syspref[@name='singleBranchMode']"/>
    <xsl:variable name="OPACTrackClicks" select="marc:sysprefs/marc:syspref[@name='TrackClicks']"/>
    <xsl:variable name="BiblioDefaultView" select="marc:sysprefs/marc:syspref[@name='BiblioDefaultView']"/>
    <xsl:variable name="leader" select="marc:leader"/>
    <xsl:variable name="leader6" select="substring($leader,7,1)"/>
    <xsl:variable name="leader7" select="substring($leader,8,1)"/>
    <xsl:variable name="leader19" select="substring($leader,20,1)"/>
    <xsl:variable name="biblionumber" select="marc:datafield[@tag=999]/marc:subfield[@code='c']"/>
    <xsl:variable name="isbn" select="marc:datafield[@tag=020]/marc:subfield[@code='a']"/>
    <xsl:variable name="controlField008" select="marc:controlfield[@tag=008]"/>
    <xsl:variable name="typeOf008">
      <xsl:choose>
        <xsl:when test="$leader19='a'">ST</xsl:when>
        <xsl:when test="$leader6='a'">
          <xsl:choose>
            <xsl:when test="$leader7='a' or $leader7='c' or $leader7='d' or $leader7='m'">BK</xsl:when>
            <xsl:when test="$leader7='b' or $leader7='i' or $leader7='s'">CR</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$leader6='t'">BK</xsl:when>
        <xsl:when test="$leader6='o' or $leader6='p'">MX</xsl:when>
        <xsl:when test="$leader6='m'">CF</xsl:when>
        <xsl:when test="$leader6='e' or $leader6='f'">MP</xsl:when>
        <xsl:when test="$leader6='g' or $leader6='k' or $leader6='r'">VM</xsl:when>
        <xsl:when test="$leader6='i' or $leader6='j'">MU</xsl:when>
        <xsl:when test="$leader6='c' or $leader6='d'">PR</xsl:when>
      </xsl:choose>
    </xsl:variable>
    <xsl:variable name="controlField008-23" select="substring($controlField008,24,1)"/>
    <xsl:variable name="controlField008-21" select="substring($controlField008,22,1)"/>
    <xsl:variable name="controlField008-22" select="substring($controlField008,23,1)"/>
    <xsl:variable name="controlField008-24" select="substring($controlField008,25,4)"/>
    <xsl:variable name="controlField008-26" select="substring($controlField008,27,1)"/>
    <xsl:variable name="controlField008-29" select="substring($controlField008,30,1)"/>
    <xsl:variable name="controlField008-34" select="substring($controlField008,35,1)"/>
    <xsl:variable name="controlField008-33" select="substring($controlField008,34,1)"/>
    <xsl:variable name="controlField008-30-31" select="substring($controlField008,31,2)"/>

    <xsl:variable name="physicalDescription">
      <xsl:if test="$typeOf008='CF' and marc:controlfield[@tag=007][substring(.,12,1)='a']">
 إعادة صياغة رقمية </xsl:if>
      <xsl:if test="$typeOf008='CF' and marc:controlfield[@tag=007][substring(.,12,1)='b']">
 مايكروفيلم مرقمن </xsl:if>
      <xsl:if test="$typeOf008='CF' and marc:controlfield[@tag=007][substring(.,12,1)='d']">
 رقمنة تناظريات أخرى </xsl:if>

      <xsl:variable name="check008-23">
        <xsl:if test="$typeOf008='BK' or $typeOf008='MU' or $typeOf008='CR' or $typeOf008='MX'">
          <xsl:value-of select="true()"></xsl:value-of>
        </xsl:if>
      </xsl:variable>
      <xsl:variable name="check008-29">
        <xsl:if test="$typeOf008='MP' or $typeOf008='VM'">
          <xsl:value-of select="true()"></xsl:value-of>
        </xsl:if>
      </xsl:variable>
      <xsl:choose>
        <xsl:when test="($check008-23 and $controlField008-23='f') or ($check008-29 and $controlField008-29='f')">
 برايل </xsl:when>
        <xsl:when test="($controlField008-23=' ' and ($leader6='c' or $leader6='d')) or (($typeOf008='BK' or $typeOf008='CR') and ($controlField008-23=' ' or $controlField008='r'))">
 طباعة</xsl:when>
        <xsl:when test="$leader6 = 'm' or ($check008-23 and $controlField008-23='s') or ($check008-29 and $controlField008-29='s')">
 الكتروني</xsl:when>
        <xsl:when test="($check008-23 and $controlField008-23='b') or ($check008-29 and $controlField008-29='b')">
 ميكروفيش</xsl:when>
        <xsl:when test="($check008-23 and $controlField008-23='a') or ($check008-29 and $controlField008-29='a')">
 ميكروفيلم</xsl:when>
        <xsl:when test="($controlField008-23='d' and ($typeOf008='BK' or $typeOf008='CR'))">
 طباعة كبيرة </xsl:when>
      </xsl:choose>
      <!--
 <xsl:if test="marc:datafield[@tag=130]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=130]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:if test="marc:datafield[@tag=240]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=240]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:if test="marc:datafield[@tag=242]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=242]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:if test="marc:datafield[@tag=245]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=245]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:if test="marc:datafield[@tag=246]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=246]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:if test="marc:datafield[@tag=730]/marc:subfield[@code='h']">
 <xsl:call-template name="chopBrackets">
 <xsl:with-param name="chopString">
 <xsl:value-of select="marc:datafield[@tag=730]/marc:subfield[@code='h']"></xsl:value-of>
 </xsl:with-param>
 </xsl:call-template>
 </xsl:if>
 <xsl:for-each select="marc:datafield[@tag=256]/marc:subfield[@code='a']">
 <xsl:value-of select="."></xsl:value-of>
 </xsl:for-each>
 <xsl:for-each select="marc:controlfield[@tag=007][substring(text(),1,1)='c']">
 <xsl:choose>
 <xsl:when test="substring(text(),14,1)='a'">
 access
 </xsl:when>
 <xsl:when test="substring(text(),14,1)='p'">
 preservation
 </xsl:when>
 <xsl:when test="substring(text(),14,1)='r'">
 replacement
 </xsl:when>
 </xsl:choose>
 </xsl:for-each>
-->
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='b']">
 شريحة خرطوشة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='c']">
        <img alt="خرطوشة قرص ضوئي للكمبيوتر" class="format" src="/opac-tmpl/lib/famfamfam/cd.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='j']">
 قرص ممغنط</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='m']">
 قرص ممغنط ضوئي</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='o']">
        <img alt="قرص ضوئي" class="format" src="/opac-tmpl/lib/famfamfam/cd.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='r']">
 متاح على الخط المباشر        <img alt="من بُعد" class="format" src="/opac-tmpl/lib/famfamfam/drive_web.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='a']">
 خرطوشة شريط</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='f']">
 شريط كاسيت</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='c'][substring(text(),2,1)='h']">
 بكرة شريط</xsl:if>

      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='d'][substring(text(),2,1)='a']">
        <img alt="كرة سماوية" class="format" src="/opac-tmpl/lib/famfamfam/world.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='d'][substring(text(),2,1)='e']">
        <img alt="كرة أرضية قمريّة" class="format" src="/opac-tmpl/lib/famfamfam/world.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='d'][substring(text(),2,1)='b']">
        <img alt="المجرة الكوكبية أو القمرية" class="format" src="/opac-tmpl/lib/famfamfam/world.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='d'][substring(text(),2,1)='c']">
        <img alt="الكرة الأرضية" class="format" src="/opac-tmpl/lib/famfamfam/world.png" />
      </xsl:if>

      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='o'][substring(text(),2,1)='o']">
 معدات</xsl:if>

      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='d']">
 أطلس </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='g']">
 رسم بياني </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='j']">
 خريطة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='q']">
 وحدة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='k']">
 ملف تعريف</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='r']">
 صورة إستشعار عن بعد</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='s']">
 قسم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='y']">
 عرض</xsl:if>

      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='a']">
 فتحه بطاقة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='e']">
 ميكروفيش</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='f']">
 كاسيت ميكروفيش</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='b']">
 خرطوشة ميكروفيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='c']">
 كاسيت ميكروفيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='d']">
 بكرة ميكروفيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='h'][substring(text(),2,1)='g']">
 مصغرة غير شفافة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='m'][substring(text(),2,1)='c']">
 خرطوشة فيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='m'][substring(text(),2,1)='f']">
 فيلم كاسيت</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='m'][substring(text(),2,1)='r']">
 بكرة فيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='n']">
        <img alt="الرسم البياني" class="format" src="/opac-tmpl/lib/famfamfam/chart_curve.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='c']">
 ملصقة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='d']">
        <img alt="رسم" class="format" src="/opac-tmpl/lib/famfamfam/pencil.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='o']">
        <img alt="بطاقة فلاش" class="format" src="/opac-tmpl/lib/famfamfam/note.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='e']">
        <img alt="اللوحة" class="format" src="/opac-tmpl/lib/famfamfam/paintbrush.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='f']">
 مكنية ضوئية للطباعة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='g']">
 الصورة السلبية</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='h']">
 طباعة الصور</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='i']">
        <img alt="صور" class="format" src="/opac-tmpl/lib/famfamfam/picture.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='j']">
 طباعة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='k'][substring(text(),2,1)='l']">
 رسم تقني</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='q'][substring(text(),2,1)='q']">
        <img alt="نوتة موسيقية" class="format" src="/opac-tmpl/lib/famfamfam/script.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='d']">
 منزلقة فيلمية</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='c']">
 خرطوشة فيلم ثابت</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='o']">
 لفافة فيلم ثابت</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='f']">
 نوع آخر للمقاطع السينمائية</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='s']">
        <img alt="شريحة" class="format" src="/opac-tmpl/lib/famfamfam/pictures.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='g'][substring(text(),2,1)='t']">
 شفاف</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='r'][substring(text(),2,1)='r']">
 صورة إستشعار عن بعد</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='e']">
 أسطوانة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='q']">
 لفافة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='g']">
 الخرطوشة الصوتية</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='s']">
 شريط كاسيت</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='d']">
        <img alt="قرص صوتي" class="format" src="/opac-tmpl/lib/famfamfam/cd.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='t']">
 صوت-بكرة الشريط</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='i']">
 صوت-مسار الفيلم</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='s'][substring(text(),2,1)='w']">
 تسجيل سلكي</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='f'][substring(text(),2,1)='c']">
 إيضاحيات</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='f'][substring(text(),2,1)='b']">
 برايل </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='f'][substring(text(),2,1)='a']">
 قمر</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='f'][substring(text(),2,1)='d']">
 عن طريق اللمس, بدون نظام كتابة </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='t'][substring(text(),2,1)='c']">
 برايل </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='t'][substring(text(),2,1)='b']">
        <img alt="طبعة كبيرة" class="format" src="/opac-tmpl/lib/famfamfam/magnifier.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='t'][substring(text(),2,1)='a']">
 طبعة منتظمة</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='t'][substring(text(),2,1)='d']">
 ‫ نص في ملف حر الصفحات </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='v'][substring(text(),2,1)='c']">
 خرطوشة فيديو</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='v'][substring(text(),2,1)='f']">
 كاسيت فيديو</xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='v'][substring(text(),2,1)='d']">
        <img alt="قرص مرئي" class="format" src="/opac-tmpl/lib/famfamfam/dvd.png" />
      </xsl:if>
      <xsl:if test="marc:controlfield[@tag=007][substring(text(),1,1)='v'][substring(text(),2,1)='r']">
 بكرة فيديو</xsl:if>
      <!--
 <xsl:for-each select="marc:datafield[@tag=856]/marc:subfield[@code='q'][string-length(.)>1]">
 <xsl:value-of select="."></xsl:value-of>
 </xsl:for-each>
 <xsl:for-each select="marc:datafield[@tag=300]">
 <xsl:call-template name="subfieldSelect">
 <xsl:with-param name="codes">abce</xsl:with-param>
 </xsl:call-template>
 </xsl:for-each>
-->
    </xsl:variable>

    <!-- Title Statement: Alternate Graphic Representation (MARC 880) -->
    <xsl:if test="$display880">
      <xsl:call-template name="m880Select">
        <xsl:with-param name="basetags">245</xsl:with-param>
        <xsl:with-param name="codes">abhfgknps</xsl:with-param>
        <xsl:with-param name="bibno">
          <xsl:value-of select="$biblionumber"/>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:if>

    <!-- title -->
    <div class="card-header">
      <input class="cb" id="bib36581" name="biblionumber" type="checkbox">
          <xsl:attribute name="value">
            <xsl:text>/cgi-bin/koha/opac-image.pl?thumbnail=1&amp;biblionumber=</xsl:text>
            <xsl:value-of select="str:encode-uri($biblionumber, true())"/>
          </xsl:attribute>
          <xsl:attribute name="id">
            <xsl:text>bib</xsl:text>
            <xsl:value-of select="str:encode-uri($biblionumber, true())"/>
          </xsl:attribute>
      </input> ‌ 
      <a>


        <xsl:attribute name="href">
          <xsl:call-template name="buildBiblioDefaultViewURL">
            <xsl:with-param name="BiblioDefaultView">
              <xsl:value-of select="$BiblioDefaultView"/>
            </xsl:with-param>
          </xsl:call-template>
          <xsl:value-of select="str:encode-uri($biblionumber, true())"/>
        </xsl:attribute>
        <xsl:attribute name="class">
          <xsl:value-of select="'title'" />
        </xsl:attribute>

        <xsl:if test="marc:datafield[@tag=245]">
          <xsl:for-each select="marc:datafield[@tag=245]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">a</xsl:with-param>
            </xsl:call-template>
            <xsl:text></xsl:text>

            <!-- 13381 add additional subfields-->
            <!-- bz 17625 adding subfields f and g -->
            <xsl:for-each select="marc:subfield[contains('bcfghknps', @code)]">
              <xsl:choose>
                <xsl:when test="@code='h'">
                  <!-- 13381 Span class around subfield h so it can be suppressed via css -->
                  <span class="title_medium">
                    <xsl:apply-templates/>
                    <xsl:text></xsl:text>
                  </span>
                </xsl:when>
                <xsl:when test="@code='c'">
                  <!-- 13381 Span class around subfield c so it can be suppressed via css -->
                  <span class="title_resp_stmt">
                    <xsl:apply-templates/>
                    <xsl:text></xsl:text>
                  </span>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:apply-templates/>
                  <xsl:text></xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:for-each>
          </xsl:for-each>
        </xsl:if>
      </a>
    </div>
    <!-- title -->
    <div class="m-2 mb-0">

      <div class="coverimages itemtype_BK">
        <img class="thumbnail">
          <xsl:attribute name="src">
            <xsl:text>/cgi-bin/koha/opac-image.pl?thumbnail=1&amp;biblionumber=</xsl:text>
            <xsl:value-of select="str:encode-uri($biblionumber, true())"/>
          </xsl:attribute>
        </img>


      </div>
      <!-- OpenURL -->
      <xsl:variable name="OPACShowOpenURL" select="marc:sysprefs/marc:syspref[@name='OPACShowOpenURL']" />
      <xsl:variable name="OpenURLImageLocation" select="marc:sysprefs/marc:syspref[@name='OpenURLImageLocation']" />
      <xsl:variable name="OpenURLText" select="marc:sysprefs/marc:syspref[@name='OpenURLText']" />
      <xsl:variable name="OpenURLResolverURL" select="marc:variables/marc:variable[@name='OpenURLResolverURL']" />

      <xsl:if test="$OPACShowOpenURL = 1 and $OpenURLResolverURL != ''">
        <xsl:variable name="openurltext">
          <xsl:choose>
            <xsl:when test="$OpenURLText != ''">
              <xsl:value-of select="$OpenURLText" />
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>OpenURL</xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        <span class="results_summary">
          <a>
            <xsl:attribute name="href">
              <xsl:value-of select="$OpenURLResolverURL" />
            </xsl:attribute>
            <xsl:attribute name="title">
              <xsl:value-of select="$openurltext" />
            </xsl:attribute>
            <xsl:attribute name="class">
              <xsl:text>OpenURL</xsl:text>
            </xsl:attribute>
            <xsl:if test="$OPACURLOpenInNewWindow='1'">
              <xsl:attribute name="target">
                <xsl:text>_فارغ</xsl:text>
              </xsl:attribute>
            </xsl:if>
            <xsl:choose>
              <xsl:when test="$OpenURLImageLocation != ''">
                <img>
                  <xsl:attribute name="src">
                    <xsl:value-of select="$OpenURLImageLocation" />
                  </xsl:attribute>
                </img>
              </xsl:when>
              <xsl:otherwise>
                <xsl:value-of select="$openurltext" />
              </xsl:otherwise>
            </xsl:choose>
          </a>
        </span>
      </xsl:if>
      <!-- End of OpenURL -->

      <p>
        <!-- Author Statement: Alternate Graphic Representation (MARC 880) -->
        <xsl:if test="$display880">
          <xsl:call-template name="m880Select">
            <xsl:with-param name="basetags">100,110,111,700,710,711</xsl:with-param>
            <xsl:with-param name="codes">abc</xsl:with-param>
          </xsl:call-template>
        </xsl:if>

        <xsl:choose>
          <xsl:when test="marc:datafield[@tag=100] or marc:datafield[@tag=110] or marc:datafield[@tag=111] or marc:datafield[@tag=700] or marc:datafield[@tag=710] or marc:datafield[@tag=711]">
            <a href="#">
              <span class="byAuthor">بواسطة </span>
              <span class="author">
                <!-- #13383 -->
                <xsl:for-each select="marc:datafield[(@tag=100 or @tag=700 or @tag=110 or @tag=710 or @tag=111 or @tag=711) and @ind1!='z']">
                  <xsl:call-template name="chopPunctuation">
                    <xsl:with-param name="chopString">
                      <xsl:call-template name="subfieldSelect">
                        <xsl:with-param name="codes">
                          <xsl:choose>
                            <!-- #13383 include subfield e for field 111 -->
                            <xsl:when test="@tag=111 or @tag=711">aeq</xsl:when>
                            <xsl:when test="@tag=110 or @tag=710">ab</xsl:when>
                            <xsl:otherwise>abcjq</xsl:otherwise>
                          </xsl:choose>
                        </xsl:with-param>
                      </xsl:call-template>
                    </xsl:with-param>
                    <xsl:with-param name="punctuation">
                      <xsl:text>:,;/ </xsl:text>
                    </xsl:with-param>
                  </xsl:call-template>
                  <!-- Display title portion for 110 and 710 fields -->
                  <xsl:if test="(@tag=110 or @tag=710) and boolean(marc:subfield[@code='c' or @code='d' or @code='n' or @code='t'])">
                    <span class="titleportion">
                      <xsl:choose>
                        <xsl:when test="marc:subfield[@code='c' or @code='d' or @code='n'][not(marc:subfield[@code='t'])]">
                          <xsl:text></xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                          <xsl:text>. </xsl:text>
                        </xsl:otherwise>
                      </xsl:choose>
                      <xsl:call-template name="chopPunctuation">
                        <xsl:with-param name="chopString">
                          <xsl:call-template name="subfieldSelect">
                            <xsl:with-param name="codes">cdnt</xsl:with-param>
                          </xsl:call-template>
                        </xsl:with-param>
                      </xsl:call-template>
                    </span>
                  </xsl:if>
                  <!-- Display title portion for 111 and 711 fields -->
                  <xsl:if test="(@tag=111 or @tag=711) and boolean(marc:subfield[@code='c' or @code='d' or @code='g' or @code='n' or @code='t'])">
                    <span class="titleportion">
                      <xsl:choose>
                        <xsl:when test="marc:subfield[@code='c' or @code='d' or @code='g' or @code='n'][not(marc:subfield[@code='t'])]">
                          <xsl:text></xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                          <xsl:text>. </xsl:text>
                        </xsl:otherwise>
                      </xsl:choose>

                      <xsl:call-template name="chopPunctuation">
                        <xsl:with-param name="chopString">
                          <xsl:call-template name="subfieldSelect">
                            <xsl:with-param name="codes">cdgnt</xsl:with-param>
                          </xsl:call-template>
                        </xsl:with-param>
                      </xsl:call-template>
                    </span>
                  </xsl:if>
                  <!-- Display dates for 100 and 700 fields -->
                  <xsl:if test="(@tag=100 or @tag=700) and marc:subfield[@code='d']">
                    <span class="authordates">
                      <xsl:text>, </xsl:text>
                      <xsl:call-template name="chopPunctuation">
                        <xsl:with-param name="chopString">
                          <xsl:call-template name="subfieldSelect">
                            <xsl:with-param name="codes">d</xsl:with-param>
                          </xsl:call-template>
                        </xsl:with-param>
                      </xsl:call-template>
                    </span>
                  </xsl:if>
                  <!-- Display title portion for 100 and 700 fields -->
                  <xsl:if test="@tag=700 and marc:subfield[@code='t']">
                    <span class="titleportion">
                      <xsl:text>. </xsl:text>
                      <xsl:call-template name="chopPunctuation">
                        <xsl:with-param name="chopString">
                          <xsl:call-template name="subfieldSelect">
                            <xsl:with-param name="codes">t</xsl:with-param>
                          </xsl:call-template>
                        </xsl:with-param>
                      </xsl:call-template>
                    </span>
                  </xsl:if>
                  <!-- Display relators for 1XX and 7XX fields -->
                  <xsl:if test="marc:subfield[@code='4' or @code='e'][not(parent::*[@tag=111])] or (self::*[@tag=111] and marc:subfield[@code='4' or @code='j'][. != ''])">
                    <span class="relatorcode">
                      <xsl:text> [</xsl:text>
                      <xsl:choose>
                        <xsl:when test="@tag=111 or @tag=711">
                          <xsl:choose>
                            <!-- Prefer j over 4 for 111 and 711 -->
                            <xsl:when test="marc:subfield[@code='j']">
                              <xsl:for-each select="marc:subfield[@code='j']">
                                <xsl:value-of select="."/>
                                <xsl:if test="position() != last()">, </xsl:if>
                              </xsl:for-each>
                            </xsl:when>
                            <xsl:otherwise>
                              <xsl:for-each select="marc:subfield[@code=4]">
                                <xsl:value-of select="."/>
                                <xsl:if test="position() != last()">, </xsl:if>
                              </xsl:for-each>
                            </xsl:otherwise>
                          </xsl:choose>
                        </xsl:when>
                        <!-- Prefer e over 4 on 100 and 110 -->
                        <xsl:when test="marc:subfield[@code='e']">
                          <xsl:for-each select="marc:subfield[@code='e'][not(@tag=111) or not(@tag=711)]">
                            <xsl:value-of select="."/>
                            <xsl:if test="position() != last()">, </xsl:if>
                          </xsl:for-each>
                        </xsl:when>
                        <xsl:otherwise>
                          <xsl:for-each select="marc:subfield[@code=4]">
                            <xsl:value-of select="."/>
                            <xsl:if test="position() != last()">, </xsl:if>
                          </xsl:for-each>
                        </xsl:otherwise>
                      </xsl:choose>
                      <xsl:text>]</xsl:text>
                    </span>
                  </xsl:if>
                  <xsl:choose>
                    <xsl:when test="position()=last()">
                      <xsl:text>.</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                      <span class="separator">
                        <xsl:text> | </xsl:text>
                      </span>
                    </xsl:otherwise>
                  </xsl:choose>
                </xsl:for-each>

              </span>
            </a>
          </xsl:when>
        </xsl:choose>
      </p>

      <xsl:call-template name="show-series">
        <xsl:with-param name="searchurl">/cgi-bin/koha/opac-search.pl</xsl:with-param>
        <xsl:with-param name="UseControlNumber" select="$UseControlNumber"/>
        <xsl:with-param name="UseAuthoritiesForTracings" select="$UseAuthoritiesForTracings"/>
      </xsl:call-template>

      <xsl:if test="marc:datafield[@tag=250]">
        <span class="results_summary edition">
          <span class="label">الطبعات: </span>
          <xsl:for-each select="marc:datafield[@tag=250]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">ab</xsl:with-param>
            </xsl:call-template>
          </xsl:for-each>
        </span>
      </xsl:if>

      <xsl:if test="marc:datafield[@tag=773]">
        <xsl:for-each select="marc:datafield[@tag=773]">
          <xsl:if test="marc:subfield[@code='t']">
            <span class="results_summary source">
              <span class="label">المصدر: </span>
              <xsl:value-of select="marc:subfield[@code='t']"/>
            </span>
          </xsl:if>
        </xsl:for-each>
      </xsl:if>

      <xsl:if test="$DisplayOPACiconsXSLT!='0'">
        <span class="results_summary type">
          <xsl:if test="$typeOf008!=''">
            <span class="results_material_type">
              <span class="label">نوع المادة: </span>
              <xsl:choose>
                <xsl:when test="$leader19='a'">
                  <img alt="ضبط" class="materialtype mt_icon_ST" src="/opac-tmpl/lib/famfamfam/ST.png" />
 ضبط</xsl:when>
                <xsl:when test="$leader6='a'">
                  <xsl:choose>
                    <xsl:when test="$leader7='c' or $leader7='d' or $leader7='m'">
                      <img alt="نص" class="materialtype mt_icon_BK" src="/opac-tmpl/lib/famfamfam/BK.png" />
 نص</xsl:when>
                    <xsl:when test="$leader7='i' or $leader7='s'">
                      <img alt="مصدر مستمر" class="materialtype mt_icon_SE" src="/opac-tmpl/lib/famfamfam/SE.png" />
 مصدر مستمر</xsl:when>
                    <xsl:when test="$leader7='a' or $leader7='b'">
                      <img alt="مقالة" class="materialtype mt_icon_AR" src="/opac-tmpl/lib/famfamfam/AR.png" />
 مقالة</xsl:when>
                  </xsl:choose>
                </xsl:when>
                <xsl:when test="$leader6='t'">
                  <img alt="نص" class="materialtype mt_icon_BK" src="/opac-tmpl/lib/famfamfam/BK.png" />
 نص</xsl:when>
                <xsl:when test="$leader6='o'">
                  <img alt="عدة" class="materialtype mt_icon_MM" src="/opac-tmpl/lib/famfamfam/MM.png" />
 عدة</xsl:when>
                <xsl:when test="$leader6='p'">
                  <img alt="مواد مختلطة" class="materialtype mt_icon_MM" src="/opac-tmpl/lib/famfamfam/MM.png" />
مواد مختلطة</xsl:when>
                <xsl:when test="$leader6='m'">
                  <img alt="ملف الحاسوب" class="materialtype mt_icon_CF" src="/opac-tmpl/lib/famfamfam/CF.png" />
 ملف الحاسوب</xsl:when>
                <xsl:when test="$leader6='e' or $leader6='f'">
                  <img alt="تخطيط" class="materialtype mt_icon_MP" src="/opac-tmpl/lib/famfamfam/MP.png" />
 تخطيط</xsl:when>
                <xsl:when test="$leader6='g'">
                  <img alt="فيلم" class="materialtype mt_icon_VM" src="/opac-tmpl/lib/famfamfam/VM.png" />
 فيلم</xsl:when>
                <xsl:when test="$leader6='k'">
                  <img alt="صورة" class="materialtype mt_icon_GR" src="/opac-tmpl/lib/famfamfam/GR.png" />
 صورة</xsl:when>
                <xsl:when test="$leader6='r'">
                  <img alt="كائن" class="materialtype mt_icon_OB" src="/opac-tmpl/lib/famfamfam/OB.png" />
 كائن</xsl:when>
                <xsl:when test="$leader6='c' or $leader6='d'">
                  <img alt="الهدف" class="materialtype mt_icon_PR" src="/opac-tmpl/lib/famfamfam/PR.png" />
 الهدف</xsl:when>
                <xsl:when test="$leader6='i'">
                  <img alt="الصوت" class="materialtype mt_icon_MU" src="/opac-tmpl/lib/famfamfam/MU.png" />
 الصوت</xsl:when>
                <xsl:when test="$leader6='j'">
                  <img alt="موسيقى" class="materialtype mt_icon_PR" src="/opac-tmpl/lib/famfamfam/PR.png" />
 موسيقى</xsl:when>
              </xsl:choose>
            </span>
          </xsl:if>
          <xsl:if test="string-length(normalize-space($physicalDescription))">
            <span class="results_format">
              <span class="label">؛ التنسيق:</span>
              <xsl:copy-of select="$physicalDescription"></xsl:copy-of>
            </span>
          </xsl:if>

          <xsl:if test="$controlField008-21 or $controlField008-22 or $controlField008-24 or $controlField008-26 or $controlField008-29 or $controlField008-34 or $controlField008-33 or $controlField008-30-31 or $controlField008-33">

            <xsl:if test="$typeOf008='CR'">
              <span class="results_typeofcontinuing">
                <xsl:if test="$controlField008-21 and $controlField008-21 !='|' and $controlField008-21 !=' '">
                  <span class="label">؛ نوع المورد المستمر:</span>
                </xsl:if>
                <xsl:choose>
                  <xsl:when test="$controlField008-21='d'">
                    <img alt="قاعدة البيانات" class="format" src="/opac-tmpl/lib/famfamfam/database.png" />
                  </xsl:when>
                  <xsl:when test="$controlField008-21='l'">
 سائبة </xsl:when>
                  <xsl:when test="$controlField008-21='m'">
 سلاسل</xsl:when>
                  <xsl:when test="$controlField008-21='n'">
 جريدة</xsl:when>
                  <xsl:when test="$controlField008-21='p'">
 دورية</xsl:when>
                  <xsl:when test="$controlField008-21='w'">
                    <img alt="موقع ويب" class="format" src="/opac-tmpl/lib/famfamfam/world_link.png" />
                  </xsl:when>
                </xsl:choose>
              </span>
            </xsl:if>
            <xsl:if test="$typeOf008='BK' or $typeOf008='CR'">
              <xsl:if test="contains($controlField008-24,'abcdefghijklmnopqrstvwxyz')">
                <span class="results_natureofcontents">
                  <span class="label">؛ طبيعة المحتويات:</span>
                  <xsl:choose>
                    <xsl:when test="contains($controlField008-24,'a')">
 نبذة أو ملخص</xsl:when>
                    <xsl:when test="contains($controlField008-24,'b')">
 الببليوغرافية                      <img alt="الببليوغرافية" class="natureofcontents" src="/opac-tmpl/lib/famfamfam/text_list_bullets.png" />
                    </xsl:when>
                    <xsl:when test="contains($controlField008-24,'c')">
 الفهرس</xsl:when>
                    <xsl:when test="contains($controlField008-24,'d')">
 قاموس </xsl:when>
                    <xsl:when test="contains($controlField008-24,'e')">
 موسوعة </xsl:when>
                    <xsl:when test="contains($controlField008-24,'f')">
 الادلة </xsl:when>
                    <xsl:when test="contains($controlField008-24,'g')">
 مقال قانوني</xsl:when>
                    <xsl:when test="contains($controlField008-24,'i')">
 فهرس </xsl:when>
                    <xsl:when test="contains($controlField008-24,'k')">
 مجموعة الإسطوانات </xsl:when>
                    <xsl:when test="contains($controlField008-24,'l')">
 التشريع </xsl:when>
                    <xsl:when test="contains($controlField008-24,'m')">
 اطروحات</xsl:when>
                    <xsl:when test="contains($controlField008-24,'n')">
 استطلاع للأدب</xsl:when>
                    <xsl:when test="contains($controlField008-24,'o')">
 مراجعة</xsl:when>
                    <xsl:when test="contains($controlField008-24,'p')">
 نصوص مبرمجة</xsl:when>
                    <xsl:when test="contains($controlField008-24,'q')">
 الأعمال الفنية</xsl:when>
                    <xsl:when test="contains($controlField008-24,'r')">
 الدليل </xsl:when>
                    <xsl:when test="contains($controlField008-24,'s')">
 إحصائيات</xsl:when>
                    <xsl:when test="contains($controlField008-24,'t')">
                      <img alt="تقرير تقني" class="natureofcontents" src="/opac-tmpl/lib/famfamfam/report.png" />
                    </xsl:when>
                    <xsl:when test="contains($controlField008-24,'v')">
 قضايا قانوينة وملاحظات القضية </xsl:when>
                    <xsl:when test="contains($controlField008-24,'w')">
 تقرير قانوني أو ملخص</xsl:when>
                    <xsl:when test="contains($controlField008-24,'z')">
 اتفاقية</xsl:when>
                  </xsl:choose>
                  <xsl:choose>
                    <xsl:when test="$controlField008-29='1'">
 مطبوع مؤتمر</xsl:when>
                  </xsl:choose>
                </span>
              </xsl:if>
            </xsl:if>
            <xsl:if test="$typeOf008='CF'">
              <span class="results_typeofcomp">
                <xsl:if test="$controlField008-26='a' or $controlField008-26='e' or $controlField008-26='f' or $controlField008-26='g'">
                  <span class="label">؛ نوع ملف الحاسب:</span>
                </xsl:if>
                <xsl:choose>
                  <xsl:when test="$controlField008-26='a'">
 بيانات رقمية</xsl:when>
                  <xsl:when test="$controlField008-26='e'">
                    <img alt="قاعدة البيانات" class="format" src="/opac-tmpl/lib/famfamfam/database.png" />
                  </xsl:when>
                  <xsl:when test="$controlField008-26='f'">
                    <img alt="خط" class="format" src="/opac-tmpl/lib/famfamfam/font.png" />
                  </xsl:when>
                  <xsl:when test="$controlField008-26='g'">
                    <img alt="لعبة" class="format" src="/opac-tmpl/lib/famfamfam/controller.png" />
                  </xsl:when>
                </xsl:choose>
              </span>
            </xsl:if>
            <xsl:if test="$typeOf008='BK'">
              <span class="results_contents_literary">
                <xsl:if test="(substring($controlField008,25,1)='j') or (substring($controlField008,25,1)='1') or ($controlField008-34='a' or $controlField008-34='b' or $controlField008-34='c' or $controlField008-34='d')">
                  <span class="label">؛ طبيعة المحتويات:</span>
                </xsl:if>
                <xsl:if test="substring($controlField008,25,1)='j'">
 براءات الاختراع </xsl:if>
                <xsl:if test="substring($controlField008,31,1)='1'">
 كتاب تذكاري</xsl:if>
                <xsl:if test="$controlField008-34='a' or $controlField008-34='b' or $controlField008-34='c' or $controlField008-34='d'">
                  <img alt="السيرة الذاتية" class="natureofcontents" src="/opac-tmpl/lib/famfamfam/user.png" />
                </xsl:if>

                <xsl:if test="$controlField008-33 and $controlField008-33!='|' and $controlField008-33!='u' and $controlField008-33!=' '">
                  <span class="label">؛ الشكل الأدبي:</span>
                </xsl:if>
                <xsl:choose>
                  <xsl:when test="$controlField008-33='0'">
 غير أدبي</xsl:when>
                  <xsl:when test="$controlField008-33='1'">
 القصة</xsl:when>
                  <xsl:when test="$controlField008-33='d'">
 دراما</xsl:when>
                  <xsl:when test="$controlField008-33='e'">
 مقالات</xsl:when>
                  <xsl:when test="$controlField008-33='f'">
 روايات</xsl:when>
                  <xsl:when test="$controlField008-33='h'">
 دعابة، سخرية، إلخ.</xsl:when>
                  <xsl:when test="$controlField008-33='i'">
 الرسائل</xsl:when>
                  <xsl:when test="$controlField008-33='j'">
 قصص قصيرة</xsl:when>
                  <xsl:when test="$controlField008-33='m'">
 أشكال مختلطة</xsl:when>
                  <xsl:when test="$controlField008-33='p'">
 شعر</xsl:when>
                  <xsl:when test="$controlField008-33='s'">
 خطب</xsl:when>
                </xsl:choose>
              </span>
            </xsl:if>
            <xsl:if test="$typeOf008='MU' and $controlField008-30-31 and $controlField008-30-31!='||' and $controlField008-30-31!='  '">
              <span class="results_literaryform">
                <span class="label">؛ الشكل الأدبي:</span>                <!-- Literary text for sound recordings -->
                <xsl:if test="contains($controlField008-30-31,'b')">
 السيرة الذاتية </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'c')">
 مطبوع مؤتمر</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'d')">
 دراما </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'e')">
 مقال </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'f')">
 خيال</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'o')">
 قصة شعبية</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'h')">
 تاريخ </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'k')">
 دعابة ، سخرية </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'m')">
 مذكرة</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'p')">
 شعر</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'r')">
 بروفة </xsl:if>
                <xsl:if test="contains($controlField008-30-31,'g')">
 التقرير</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'s')">
 صوت</xsl:if>
                <xsl:if test="contains($controlField008-30-31,'l')">
 خطاب</xsl:if>
              </span>
            </xsl:if>
            <xsl:if test="$typeOf008='VM'">
              <span class="results_typeofvisual">
                <span class="label">؛ نوع المادة المرئية:</span>
                <xsl:choose>
                  <xsl:when test="$controlField008-33='a'">
 فن أصلى</xsl:when>
                  <xsl:when test="$controlField008-33='b'">
 معدات</xsl:when>
                  <xsl:when test="$controlField008-33='c'">
 استنساخ فني</xsl:when>
                  <xsl:when test="$controlField008-33='d'">
 الديوراما </xsl:when>
                  <xsl:when test="$controlField008-33='f'">
 فيلم ثابت</xsl:when>
                  <xsl:when test="$controlField008-33='g'">
 لعبة</xsl:when>
                  <xsl:when test="$controlField008-33='i'">
 صور</xsl:when>
                  <xsl:when test="$controlField008-33='k'">
 جرافيك</xsl:when>
                  <xsl:when test="$controlField008-33='l'">
 رسم تقني</xsl:when>
                  <xsl:when test="$controlField008-33='m'">
 صورة متحركة</xsl:when>
                  <xsl:when test="$controlField008-33='n'">
 الرسم البياني</xsl:when>
                  <xsl:when test="$controlField008-33='o'">
 بطاقة فلاش</xsl:when>
                  <xsl:when test="$controlField008-33='p'">
 شريحة مجهر</xsl:when>
                  <xsl:when test="$controlField008-33='q' or marc:controlfield[@tag=007][substring(text(),1,1)='a'][substring(text(),2,1)='q']">
 وحدة</xsl:when>
                  <xsl:when test="$controlField008-33='r'">
 حقائق </xsl:when>
                  <xsl:when test="$controlField008-33='s'">
 شريحة</xsl:when>
                  <xsl:when test="$controlField008-33='t'">
 شفاف</xsl:when>
                  <xsl:when test="$controlField008-33='v'">
 تسجيل فيديو</xsl:when>
                  <xsl:when test="$controlField008-33='w'">
 لعبة</xsl:when>
                </xsl:choose>
              </span>
            </xsl:if>
          </xsl:if>

          <xsl:if test="($typeOf008='BK' or $typeOf008='CF' or $typeOf008='MU' or $typeOf008='VM') and ($controlField008-22='a' or $controlField008-22='b' or $controlField008-22='c' or $controlField008-22='d' or $controlField008-22='e' or $controlField008-22='g' or $controlField008-22='j' or $controlField008-22='f')">
            <span class="results_audience">
              <span class="label">؛ الجمهور:</span>
              <xsl:choose>
                <xsl:when test="$controlField008-22='a'">
 مرحلة ما قبل المدرسة;</xsl:when>
                <xsl:when test="$controlField008-22='b'">
 أساسي;</xsl:when>
                <xsl:when test="$controlField008-22='c'">
 مرحلة ما قبل المراهقة;</xsl:when>
                <xsl:when test="$controlField008-22='d'">
 مراهق؛</xsl:when>
                <xsl:when test="$controlField008-22='e'">
 بالغ؛</xsl:when>
                <xsl:when test="$controlField008-22='g'">
 عام; </xsl:when>
                <xsl:when test="$controlField008-22='j'">
 حدث (شاب);</xsl:when>
                <xsl:when test="$controlField008-22='f'">
 متخصص;</xsl:when>
              </xsl:choose>
            </span>
          </xsl:if>
          <xsl:text></xsl:text>          <!-- added blank space to fix font display problem, see Bug 3671 -->
        </span>
      </xsl:if>

      <xsl:call-template name="show-lang-041"/>

      <!-- Publisher Statement: Alternate Graphic Representation (MARC 880) -->
      <xsl:if test="$display880">
        <xsl:call-template name="m880Select">
          <xsl:with-param name="basetags">260</xsl:with-param>
          <xsl:with-param name="codes">abcg</xsl:with-param>
          <xsl:with-param name="class">ملخص النتائج الناشر</xsl:with-param>
          <xsl:with-param name="label">تفاصيل النشر:</xsl:with-param>
        </xsl:call-template>
      </xsl:if>

      <!-- Publisher or Distributor Number -->
      <xsl:if test="marc:datafield[@tag=028]">
        <span class="results_summary publisher_number ">
          <span class="label">رقم الناشر:</span>
          <xsl:for-each select="marc:datafield[@tag=028]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">abq</xsl:with-param>
              <xsl:with-param name="delimeter">
                <xsl:text> | </xsl:text>
              </xsl:with-param>
            </xsl:call-template>
          </xsl:for-each>
        </span>
      </xsl:if>

      <!-- Publisher info and RDA related info from tags 260, 264 -->
      <xsl:choose>
        <xsl:when test="marc:datafield[@tag=264]">
          <xsl:call-template name="showRDAtag264"/>
        </xsl:when>
        <xsl:when test="marc:datafield[@tag=260]">
          <span class="results_summary publisher">
            <span class="label">تفاصيل النشر: </span>
            <xsl:for-each select="marc:datafield[@tag=260]">
              <xsl:if test="marc:subfield[@code='a']">
                <span class="publisher_place" property="location">
                  <xsl:call-template name="subfieldSelect">
                    <xsl:with-param name="codes">a</xsl:with-param>
                  </xsl:call-template>
                </span>
              </xsl:if>
              <xsl:text></xsl:text>
              <xsl:if test="marc:subfield[@code='b']">
                <span property="name" class="publisher_name">
                  <xsl:call-template name="subfieldSelect">
                    <xsl:with-param name="codes">b</xsl:with-param>
                  </xsl:call-template>
                </span>
              </xsl:if>
              <xsl:text></xsl:text>
              <span property="datePublished" class="publisher_date">
                <xsl:call-template name="chopPunctuation">
                  <xsl:with-param name="chopString">
                    <xsl:call-template name="subfieldSelect">
                      <xsl:with-param name="codes">cg</xsl:with-param>
                    </xsl:call-template>
                  </xsl:with-param>
                </xsl:call-template>
              </span>
              <xsl:choose>
                <xsl:when test="position()=last()">
                  <xsl:text></xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>; </xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:for-each>
            <xsl:if test="marc:datafield[@tag=264]">
              <xsl:text>; </xsl:text>
              <xsl:call-template name="showRDAtag264"/>
            </xsl:if>
          </span>
        </xsl:when>
      </xsl:choose>

      <!-- Dissertation note -->
      <xsl:if test="marc:datafield[@tag=502]">
        <span class="results_summary diss_note">
          <span class="label">ملاحظة الأطروحة:</span>
          <xsl:for-each select="marc:datafield[@tag=502]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">abcdgo</xsl:with-param>
            </xsl:call-template>
          </xsl:for-each>
          <xsl:choose>
            <xsl:when test="position()=last()">
              <xsl:text></xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text></xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </span>
      </xsl:if>

      <!-- Other Title Statement: Alternate Graphic Representation (MARC 880) -->
      <xsl:if test="$display880">
        <xsl:call-template name="m880Select">
          <xsl:with-param name="basetags">246</xsl:with-param>
          <xsl:with-param name="codes">ab</xsl:with-param>
          <xsl:with-param name="class">ملخص النتائج عنوان آخر</xsl:with-param>
          <xsl:with-param name="label">عنوان آخر: </xsl:with-param>
        </xsl:call-template>
      </xsl:if>

      <xsl:if test="marc:datafield[@tag=246]">
        <span class="results_summary other_title">
          <span class="label">عنوان آخر: </span>
          <xsl:for-each select="marc:datafield[@tag=246]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">ab</xsl:with-param>
            </xsl:call-template>
            <!-- #13386 added separator | -->
            <xsl:choose>
              <xsl:when test="position()=last()">
                <xsl:text>.</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <span class="separator">
                  <xsl:text> | </xsl:text>
                </span>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:for-each>
        </span>
      </xsl:if>



      <xsl:if test="marc:datafield[@tag=242]">
        <span class="results_summary translated_title">
          <span class="label">العنوان المترجم:</span>
          <xsl:for-each select="marc:datafield[@tag=242]">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">abh</xsl:with-param>
            </xsl:call-template>
            <xsl:choose>
              <xsl:when test="position()=last()">
                <xsl:text>.</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>; </xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:for-each>
        </span>
      </xsl:if>
      <xsl:if test="marc:datafield[@tag=856]">
        <span class="results_summary online_resources">
          <span class="label">الوصول إلى الانترنت: </span>
          <xsl:for-each select="marc:datafield[@tag=856]">
            <xsl:variable name="SubqText">
              <xsl:value-of select="marc:subfield[@code='q']"/>
            </xsl:variable>
            <xsl:if test="$OPACURLOpenInNewWindow='0'">
              <a>
                <xsl:choose>
                  <xsl:when test="$OPACTrackClicks='track'">
                    <xsl:attribute name="href">/cgi-bin/koha/tracklinks.pl?uri=<xsl:value-of select="str:encode-uri(marc:subfield[@code='u'], true())"/>
&amp;biblionumber=<xsl:value-of select="$biblionumber"/>
                  </xsl:attribute>
                </xsl:when>
                <xsl:when test="$OPACTrackClicks='anonymous'">
                  <xsl:attribute name="href">/cgi-bin/koha/tracklinks.pl?uri=<xsl:value-of select="str:encode-uri(marc:subfield[@code='u'], true())"/>
&amp;biblionumber=<xsl:value-of select="$biblionumber"/>
                </xsl:attribute>
              </xsl:when>
              <xsl:otherwise>
                <xsl:attribute name="href">
                  <xsl:if test="not(contains(marc:subfield[@code='u'],'://'))">
                    <xsl:choose>
                      <xsl:when test="@ind1=7">
                        <xsl:value-of select="marc:subfield[@code='2']"/>
                        <xsl:text>://</xsl:text>
                      </xsl:when>
                      <xsl:when test="@ind1=1">
                        <xsl:text>ftp://</xsl:text>
                      </xsl:when>
                      <xsl:otherwise>
                        <xsl:text>http://</xsl:text>
                      </xsl:otherwise>
                    </xsl:choose>
                  </xsl:if>
                  <xsl:value-of select="marc:subfield[@code='u']"/>
                </xsl:attribute>
              </xsl:otherwise>
            </xsl:choose>
            <xsl:choose>
              <xsl:when test="($Show856uAsImage='Results' or $Show856uAsImage='Both') and (substring($SubqText,1,6)='image/' or $SubqText='img' or $SubqText='bmp' or $SubqText='cod' or $SubqText='gif' or $SubqText='ief' or $SubqText='jpe' or $SubqText='jpeg' or $SubqText='jpg' or $SubqText='jfif' or $SubqText='png' or $SubqText='svg' or $SubqText='tif' or $SubqText='tiff' or $SubqText='ras' or $SubqText='cmx' or $SubqText='ico' or $SubqText='pnm' or $SubqText='pbm' or $SubqText='pgm' or $SubqText='ppm' or $SubqText='rgb' or $SubqText='xbm' or $SubqText='xpm' or $SubqText='xwd')">
                <xsl:element name="img">
                  <xsl:attribute name="src">
                    <xsl:value-of select="marc:subfield[@code='u']"/>
                  </xsl:attribute>
                  <xsl:attribute name="alt">
                    <xsl:value-of select="marc:subfield[@code='y']"/>
                  </xsl:attribute>
                  <xsl:attribute name="style">الارتفاع: 100 بيكسل؛</xsl:attribute>
                </xsl:element>
                <xsl:text></xsl:text>
              </xsl:when>
              <xsl:when test="marc:subfield[@code='y' or @code='3' or @code='z']">
                <xsl:call-template name="subfieldSelect">
                  <xsl:with-param name="codes">y3z</xsl:with-param>
                </xsl:call-template>
              </xsl:when>
              <xsl:when test="not(marc:subfield[@code='y']) and not(marc:subfield[@code='3']) and not(marc:subfield[@code='z'])">
                <xsl:choose>
                  <xsl:when test="$URLLinkText!=''">
                    <xsl:value-of select="$URLLinkText"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>اضغط هنا للوصول بشكل مباشر</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:when>
            </xsl:choose>
          </a>
        </xsl:if>
        <xsl:if test="$OPACURLOpenInNewWindow='1'">
          <a target='_blank'>
            <xsl:choose>
              <xsl:when test="$OPACTrackClicks='track'">
                <xsl:attribute name="href">/cgi-bin/koha/tracklinks.pl?uri=<xsl:value-of select="str:encode-uri(marc:subfield[@code='u'], true())"/>
&amp;biblionumber=<xsl:value-of select="$biblionumber"/>
              </xsl:attribute>
            </xsl:when>
            <xsl:when test="$OPACTrackClicks='anonymous'">
              <xsl:attribute name="href">/cgi-bin/koha/tracklinks.pl?uri=<xsl:value-of select="str:encode-uri(marc:subfield[@code='u'], true())"/>
&amp;biblionumber=<xsl:value-of select="$biblionumber"/>
            </xsl:attribute>
          </xsl:when>
          <xsl:otherwise>
            <xsl:attribute name="href">
              <xsl:value-of select="marc:subfield[@code='u']"/>
            </xsl:attribute>
          </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
          <xsl:when test="($Show856uAsImage='Results' or $Show856uAsImage='Both') and ($SubqText='img' or $SubqText='bmp' or $SubqText='cod' or $SubqText='gif' or $SubqText='ief' or $SubqText='jpe' or $SubqText='jpeg' or $SubqText='jpg' or $SubqText='jfif' or $SubqText='png' or $SubqText='svg' or $SubqText='tif' or $SubqText='tiff' or $SubqText='ras' or $SubqText='cmx' or $SubqText='ico' or $SubqText='pnm' or $SubqText='pbm' or $SubqText='pgm' or $SubqText='ppm' or $SubqText='rgb' or $SubqText='xbm' or $SubqText='xpm' or $SubqText='xwd')">
            <xsl:element name="img">
              <xsl:attribute name="src">
                <xsl:value-of select="marc:subfield[@code='u']"/>
              </xsl:attribute>
              <xsl:attribute name="alt">
                <xsl:value-of select="marc:subfield[@code='y']"/>
              </xsl:attribute>
              <xsl:attribute name="style">الارتفاع: 100 بيكسل</xsl:attribute>
            </xsl:element>
            <xsl:text></xsl:text>
          </xsl:when>
          <xsl:when test="marc:subfield[@code='y' or @code='3' or @code='z']">
            <xsl:call-template name="subfieldSelect">
              <xsl:with-param name="codes">y3z</xsl:with-param>
            </xsl:call-template>
          </xsl:when>
          <xsl:when test="not(marc:subfield[@code='y']) and not(marc:subfield[@code='3']) and not(marc:subfield[@code='z'])">
            <xsl:choose>
              <xsl:when test="$URLLinkText!=''">
                <xsl:value-of select="$URLLinkText"/>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>اضغط هنا للوصول بشكل مباشر</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:when>
        </xsl:choose>
      </a>
    </xsl:if>
    <xsl:choose>
      <xsl:when test="position()=last()">
        <xsl:text></xsl:text>
      </xsl:when>
      <xsl:otherwise> | </xsl:otherwise>
    </xsl:choose>
  </xsl:for-each>
</span>
</xsl:if>


<!-- Availability line -->
<span class="results_summary availability">
<span class="label">الإتاحة: </span>
<xsl:variable name="sumAv" select="count(key('item-by-status', 'available'))"/>
<xsl:variable name="sumRef" select="count(key('item-by-status', 'reference'))"/>

<xsl:choose>
  <xsl:when test="$itemcount=0">
    <xsl:choose>
      <xsl:when test="string-length($AlternateHoldingsField)=3 and marc:datafield[@tag=$AlternateHoldingsField]">
        <xsl:variable name="AlternateHoldingsCount" select="count(marc:datafield[@tag=$AlternateHoldingsField])"/>
        <xsl:for-each select="marc:datafield[@tag=$AlternateHoldingsField][1]">
          <xsl:call-template name="subfieldSelect">
            <xsl:with-param name="codes">
              <xsl:value-of select="$AlternateHoldingsSubfields"/>
            </xsl:with-param>
            <xsl:with-param name="delimeter">
              <xsl:value-of select="$AlternateHoldingsSeparator"/>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:for-each>
 (        <xsl:value-of select="$AlternateHoldingsCount"/>
)
      </xsl:when>
      <xsl:otherwise>
        <span class="noitems">No items available.</span>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:when>
  <xsl:when test="$sumAv>0">
    <span class="available reallyavailable">
      <span class="AvailabilityLabel">
        <strong>
          <xsl:text>المواد المتاحة للإعارة:</xsl:text>
        </strong>
      </span>
      <xsl:variable name="available_items" select="key('item-by-status', 'available')"/>
      <xsl:choose>
        <xsl:when test="$singleBranchMode=1">
          <xsl:for-each select="$available_items[generate-id() = generate-id(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch))[1])]">
            <span class="ItemSummary">
              <xsl:value-of select="count(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch)))"/>
              <xsl:text></xsl:text>
              <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber and $OPACItemLocation='callnum'">
                <span class="CallNumberAndLabel">
                  <span class="LabelCallNumber">رقم الطلب</span>
                  <span class="CallNumber">
                    <xsl:value-of select="items:itemcallnumber"/>
                    <xsl:if test="count(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch)))>1">
                      <xsl:text>, ..</xsl:text>
                    </xsl:if>
                  </span>
                </span>
              </xsl:if>
              <xsl:choose>
                <xsl:when test="position()=last()">
                  <xsl:text>. </xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>, </xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </span>
          </xsl:for-each>
        </xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="$OPACResultsLibrary='homebranch'">
              <xsl:for-each select="$available_items[generate-id() = generate-id(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch))[1])]">
                <span class="ItemSummary">
                  <span class="ItemBranch">
                    <xsl:value-of select="items:homebranch"/>
                  </span>
                  <xsl:text> (</xsl:text>
                  <xsl:value-of select="count(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch)))"/>
                  <xsl:text>) </xsl:text>
                  <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber and $OPACItemLocation='callnum'">
                    <span class="CallNumberAndLabel">
                      <span class="LabelCallNumber">رقم الطلب</span>
                      <span class="CallNumber">
                        <xsl:value-of select="items:itemcallnumber"/>
                        <xsl:if test="count(key('item-by-status-and-branch-holding', concat(items:status, ' ', items:holdingbranch)))>1">
                          <xsl:text>, ..</xsl:text>
                        </xsl:if>
                      </span>
                    </span>
                  </xsl:if>
                  <xsl:choose>
                    <xsl:when test="position()=last()">
                      <xsl:text>. </xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                      <xsl:text>, </xsl:text>
                    </xsl:otherwise>
                  </xsl:choose>
                </span>
              </xsl:for-each>
            </xsl:when>
            <xsl:otherwise>
              <xsl:for-each select="$available_items[generate-id() = generate-id(key('item-by-status-and-branch-holding', concat(items:status, ' ', items:holdingbranch))[1])]">
                <span class="ItemSummary">
                  <span class="ItemBranch">
                    <xsl:value-of select="items:holdingbranch"/>
                  </span>
                  <xsl:text> (</xsl:text>
                  <xsl:value-of select="count(key('item-by-status-and-branch-holding', concat(items:status, ' ', items:holdingbranch)))"/>
                  <xsl:text>) </xsl:text>
                  <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber and $OPACItemLocation='callnum'">
                    <span class="CallNumberAndLabel">
                      <span class="LabelCallNumber">رقم الطلب</span>
                      <span class="CallNumber">
                        <xsl:value-of select="items:itemcallnumber"/>
                        <xsl:if test="count(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch)))>1">
                          <xsl:text>, ..</xsl:text>
                        </xsl:if>
                      </span>
                    </span>
                  </xsl:if>
                  <xsl:choose>
                    <xsl:when test="position()=last()">
                      <xsl:text>. </xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                      <xsl:text>, </xsl:text>
                    </xsl:otherwise>
                  </xsl:choose>
                </span>
              </xsl:for-each>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
    </span>
  </xsl:when>
</xsl:choose>

<xsl:choose>
  <xsl:when test="$sumRef>0">
    <span class="available reference">
      <span class="AvailabilityLabel">
        <strong>
          <xsl:text>المواد المتاحة للمرجعية:</xsl:text>
        </strong>
      </span>
      <xsl:variable name="reference_items" select="key('item-by-status', 'reference')"/>
      <xsl:for-each select="$reference_items[generate-id() = generate-id(key('item-by-substatus-and-branch', concat(items:substatus, ' ', items:homebranch))[1])]">
        <span>
          <xsl:attribute name="class">
 ملخص العنصر:            <xsl:value-of select="translate(items:substatus,' ','_')"/>
          </xsl:attribute>
          <xsl:if test="$singleBranchMode=0">
            <span class="ItemBranch">
              <xsl:value-of select="items:homebranch"/>
              <xsl:text></xsl:text>
            </span>
          </xsl:if>
          <span class='notforloandesc'>
            <xsl:value-of select="items:substatus"/>
          </span>
          <xsl:text> (</xsl:text>
          <xsl:value-of select="count(key('item-by-substatus-and-branch', concat(items:substatus, ' ', items:homebranch)))"/>
          <xsl:text>) </xsl:text>
          <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber and $OPACItemLocation='callnum'">
            <span class="CallNumberAndLabel">
              <span class="LabelCallNumber">رقم الطلب</span>
              <span class="CallNumber">
                <xsl:value-of select="items:itemcallnumber"/>
                <xsl:if test="count(key('item-by-substatus-and-branch', concat(items:substatus, ' ', items:homebranch)))>1">
                  <xsl:text>, ..</xsl:text>
                </xsl:if>
              </span>
            </span>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="position()=last()">
              <xsl:text>. </xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>, </xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </span>
      </xsl:for-each>
    </span>
  </xsl:when>
</xsl:choose>

<xsl:choose>
  <xsl:when test="number($sumAv+$sumRef) &lt; number($itemcount)">
    <span class="unavailable">
      <span class="AvailabilityLabel">
        <strong>
          <xsl:text>Not available: </xsl:text>
        </strong>
      </span>

      <!-- First the remaining not for loan categories -->
      <xsl:variable name="unavailable_items" select="key('item-by-status', 'reallynotforloan')"/>
      <xsl:for-each select="$unavailable_items[not(./items:substatus=preceding-sibling::*/items:substatus)]">
        <span class="ItemSummary unavailable">
          <span class='notforloandesc'>
            <xsl:value-of select="items:substatus"/>
          </span>
          <xsl:text> (</xsl:text>
          <xsl:value-of select="count(parent::*/items:item/items:substatus[ text() = current()/items:substatus  ])"/>
          <xsl:text>)</xsl:text>
          <xsl:choose>
            <xsl:when test="position()=last()">
              <xsl:text>. </xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>, </xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </span>
      </xsl:for-each>

      <!-- Followed by other statuses -->
      <xsl:if test="count(key('item-by-status', 'Checked out'))>0">
        <span class="unavailable">
          <xsl:text>المعار (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Checked out'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="count(key('item-by-status', 'Withdrawn'))>0">
        <span class="unavailable">
          <xsl:text>مسحوب (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Withdrawn'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="$hidelostitems='0' and count(key('item-by-status', 'Lost'))>0">
        <span class="unavailable">
          <xsl:text>مفقود (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Lost'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="count(key('item-by-status', 'Damaged'))>0">
        <span class="unavailable">
          <xsl:text>تالف (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Damaged'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="count(key('item-by-status', 'Pending hold'))>0">
        <span class="unavailable">
          <xsl:text>حجز في الانتظار (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Pending hold'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="count(key('item-by-status', 'In transit'))>0">
        <span class="unavailable">
          <xsl:text>في النقل (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'In transit'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
      <xsl:if test="count(key('item-by-status', 'Waiting'))>0">
        <span class="unavailable">
          <xsl:text>في الحجز (</xsl:text>
          <xsl:value-of select="count(key('item-by-status', 'Waiting'))"/>
          <xsl:text>). </xsl:text>
        </span>
      </xsl:if>
    </span>
  </xsl:when>
</xsl:choose>
</span>
<!-- End of Availability line -->
</div><!-- m.2 -->

<!-- Location line -->
<xsl:choose>
<xsl:when test="($OPACItemLocation='location' or $OPACItemLocation='ccode') and (count(key('item-by-status', 'available'))!=0 or count(key('item-by-status', 'reference'))!=0)">
<span class="results_summary location">

  <xsl:choose>
    <xsl:when test="$OPACItemLocation='location'">
      <span class="label">الموقع:</span>
    </xsl:when>
    <xsl:when test="$OPACItemLocation='ccode'">
      <span class="label">مجموعة (مجموعات): </span>
    </xsl:when>
  </xsl:choose>

  <xsl:choose>
    <xsl:when test="count(key('item-by-status', 'available'))>0">
      <span class="available">
        <xsl:variable name="available_items" select="key('item-by-status', 'available')"/>
        <xsl:for-each select="$available_items[generate-id() = generate-id(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch))[1])]">
          <xsl:choose>
            <xsl:when test="$OPACItemLocation='location'">
              <strong>
                <xsl:value-of select="concat(items:location,' ')"/>
              </strong>
            </xsl:when>
            <xsl:when test="$OPACItemLocation='ccode'">
              <strong>
                <xsl:value-of select="concat(items:ccode,' ')"/>
              </strong>
            </xsl:when>
          </xsl:choose>
          <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber">
            <span class="CallNumberAndLabel">
              <span class="LabelCallNumber">رقم الطلب</span>
              <span class="CallNumber">
                <xsl:value-of select="items:itemcallnumber"/>
              </span>
            </span>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="position()=last()">
              <xsl:text>. </xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>, </xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </span>
    </xsl:when>
    <xsl:when test="count(key('item-by-status', 'reference'))>0">
      <span class="available">
        <xsl:variable name="reference_items" select="key('item-by-status', 'reference')"/>
        <xsl:for-each select="$reference_items[generate-id() = generate-id(key('item-by-status-and-branch-home', concat(items:status, ' ', items:homebranch))[1])]">
          <xsl:choose>
            <xsl:when test="$OPACItemLocation='location'">
              <strong>
                <xsl:value-of select="concat(items:location,' ')"/>
              </strong>
            </xsl:when>
            <xsl:when test="$OPACItemLocation='ccode'">
              <strong>
                <xsl:value-of select="concat(items:ccode,' ')"/>
              </strong>
            </xsl:when>
          </xsl:choose>
          <xsl:if test="items:itemcallnumber != '' and items:itemcallnumber">
            <span class="CallNumberAndLabel">
              <span class="LabelCallNumber">رقم الطلب</span>
              <span class="CallNumber">
                <xsl:value-of select="items:itemcallnumber"/>
              </span>
            </span>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="position()=last()">
              <xsl:text>. </xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>, </xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </span>
    </xsl:when>
  </xsl:choose>
</span>
</xsl:when>
</xsl:choose>
<!-- End of Location line -->

</xsl:template>

<xsl:template name="nameABCQ">
<xsl:call-template name="chopPunctuation">
<xsl:with-param name="chopString">
<xsl:call-template name="subfieldSelect">
  <xsl:with-param name="codes">abcq</xsl:with-param>
</xsl:call-template>
</xsl:with-param>
<xsl:with-param name="punctuation">
<xsl:text>:,;/ </xsl:text>
</xsl:with-param>
</xsl:call-template>
</xsl:template>

<xsl:template name="nameABCDN">
<xsl:call-template name="chopPunctuation">
<xsl:with-param name="chopString">
<xsl:call-template name="subfieldSelect">
  <xsl:with-param name="codes">abcdn</xsl:with-param>
</xsl:call-template>
</xsl:with-param>
<xsl:with-param name="punctuation">
<xsl:text>:,;/ </xsl:text>
</xsl:with-param>
</xsl:call-template>
</xsl:template>

<xsl:template name="nameACDEQ">
<xsl:call-template name="subfieldSelect">
<xsl:with-param name="codes">acdeq</xsl:with-param>
</xsl:call-template>
</xsl:template>

<xsl:template name="nameDate">
<xsl:for-each select="marc:subfield[@code='d']">
<xsl:call-template name="chopPunctuation">
<xsl:with-param name="chopString" select="."/>
</xsl:call-template>
</xsl:for-each>
</xsl:template>

<xsl:template name="role">
<xsl:for-each select="marc:subfield[@code='e']">
<xsl:value-of select="."/>
</xsl:for-each>
<xsl:for-each select="marc:subfield[@code='4']">
<xsl:value-of select="."/>
</xsl:for-each>
</xsl:template>

<xsl:template name="specialSubfieldSelect">
<xsl:param name="anyCodes"/>
<xsl:param name="axis"/>
<xsl:param name="beforeCodes"/>
<xsl:param name="afterCodes"/>
<xsl:variable name="str">
<xsl:for-each select="marc:subfield">
<xsl:if test="contains($anyCodes, @code) or (contains($beforeCodes,@code) and following-sibling::marc:subfield[@code=$axis]) or (contains($afterCodes,@code) and preceding-sibling::marc:subfield[@code=$axis])">
  <xsl:value-of select="text()"/>
  <xsl:text></xsl:text>
</xsl:if>
</xsl:for-each>
</xsl:variable>
<xsl:value-of select="substring($str,1,string-length($str)-1)"/>
</xsl:template>

<xsl:template name="subtitle">
<xsl:if test="marc:subfield[@code='b']">
<xsl:call-template name="chopPunctuation">
<xsl:with-param name="chopString">
  <xsl:value-of select="marc:subfield[@code='b']"/>

  <!--<xsl:call-template name="subfieldSelect">
 <xsl:with-param name="codes">b</xsl:with-param>
 </xsl:call-template>-->
</xsl:with-param>
</xsl:call-template>
</xsl:if>
</xsl:template>

<xsl:template name="chopBrackets">
<xsl:param name="chopString"></xsl:param>
<xsl:variable name="string">
<xsl:call-template name="chopPunctuation">
<xsl:with-param name="chopString" select="$chopString"></xsl:with-param>
</xsl:call-template>
</xsl:variable>
<xsl:if test="substring($string, 1,1)='['">
<xsl:value-of select="substring($string,2, string-length($string)-2)"></xsl:value-of>
</xsl:if>
<xsl:if test="substring($string, 1,1)!='['">
<xsl:value-of select="$string"></xsl:value-of>
</xsl:if>
</xsl:template>

</xsl:stylesheet>
