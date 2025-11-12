[% USE Koha %]
[% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && loggedinusername ) %]
 <div id="menu">
 <ul>
 [% IF ( userview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-user.pl">ملخصك</a></li>
 [% IF ( OPACFinesTab ) %]
 [% IF ( accountview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-account.pl">رسومك</a></li>
 [% END %]

 [% IF ( userupdateview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-memberentry.pl">تفاصيلك الشخصية</a></li>

 [% IF Koha.Preference('GDPR_Policy') # remove when extending %]
 [% IF consentview %]<li class="active">[% ELSE %]<li>[% END %]
 <a href="/cgi-bin/koha/opac-patron-consent.pl">موافقاتك</a>
 </li>
 [% END %]

 [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]
 [% IF ( tagsview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-tags.pl?mine=1">وسومك</a></li>
 [% END %]

 [% IF logged_in_user.category.effective_change_password %]
 [% IF ( passwdview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-passwd.pl">تغيير كلمة مرورك</a></li>
 [% END %]

 [% IF EnableOpacSearchHistory %]
 [% IF ( searchhistoryview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-search-history.pl">سِجل بحثك</a></li>
 [% END %]

 [% IF ( opacreadinghistory ) %]
 [% IF ( readingrecview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-readingrecord.pl">سجل إعاراتك</a></li>
 [% IF ( OPACPrivacy ) %]
 [% IF ( privacyview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-privacy.pl">خصوصيتك</a></li>
 [% END %]
 [% END # / opacreadinghistory %]

 [% IF Koha.Preference('OPACHoldsHistory') == 1 %]
 [% IF ( holdshistoryview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-holdshistory.pl">سجل حجوزاتك</a></li>
 [% END %]

 [% IF Koha.Preference( 'suggestion' ) == 1 %]
 [% IF ( suggestionsview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-suggestions.pl">مقترحات الشراء الخاصة بك</a></li>
 [% END %]

 [% IF ( EnhancedMessagingPreferences ) %]
 [% IF Koha.Preference( 'EnhancedMessagingPreferencesOPAC' ) %]
 [% IF ( messagingview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-messaging.pl">مراسلاتك</a></li>
 [% END %]
 [% END %]

 [% IF Koha.Preference( 'virtualshelves' ) == 1 %]
 [% IF ( listsview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=1">قوائمك</a></li>
 [% END %]

 [% IF Koha.Preference( 'RoutingSerials' ) && logged_in_user && logged_in_user.get_routing_lists.count %]
 [% IF ( routinglistsview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-routing-lists.pl">قوائم التمرير الخاصة بك</a></li>
 [% END %]

 [% IF Koha.Preference( 'useDischarge' ) == 1 %]
 [% IF ( dischargeview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-discharge.pl">طلب الإخلاء</a></li>
 [% END %]

 [% IF Koha.Preference( 'ILLModule' ) == 1 %]
 [% IF ( illrequestsview ) %]
 <li class="active">
 [% ELSE %]
 <li>
 [% END %]
 <a href="/cgi-bin/koha/opac-illrequests.pl">طلبات الإعارة بين المكتبات الخاصة بك</a></li>
 [% END %]

 </ul>
 </div>
[% END %]
