[% USE Branches %]
[% USE AuthorisedValues %]
[% SET itemavailable = 1 %]

[%#- This include takes two parameters: an item structure -%]
[%#- and an optional loan (issue) structure.  The issue -%]
[%#- structure is used by course reserves pages, which do -%]
[%#- not use an API to fetch items that populates item.datedue. -%]

[% IF ( item.itemlost ) %]
 [% SET itemavailable = 0 %]
 [% av_lib_include = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.itemlost', authorised_value => item.itemlost, opac => 1 ) %]
 [% IF ( av_lib_include ) %]
 <span class="item-status lost">[% av_lib_include | html %]</span>
 [% ELSE %]
 <span class="item-status lost">مادة مفقودة</span>
 [% END %]
[% END %]

[% IF item.isa('Koha::Item') %]
 [% SET datedue = issue.date_due %]
 [% SET onsite_checkout = issue.onsite_checkout %]
[% ELSE %]
 [% SET datedue = item.datedue || issue.date_due %]
 [% SET onsite_checkout = item.onsite_checkout %]
[% END %]
[% IF datedue %]
 [% SET itemavailable = 0 %]
 [% IF onsite_checkout %]
 [% IF ( OPACShowCheckoutName ) %]
 <span class="item-status checkedout">حاليا قيد الاستخدام المحلي بواسطة [% item.firstname | html %] [% item.surname | html %] [% IF ( item.cardnumber ) %]([% item.cardnumber | html %])[% END %]</span>
 [% ELSE %]
 <span class="item-status checkedout">قيد الاستخدام المحلي حاليا</span>
 [% END %]
 [% ELSE %]
 [% IF ( OPACShowCheckoutName ) %]
 <span class="item-status checkedout">معار إلى [% item.firstname | html %] [% item.surname | html %] [% IF ( item.cardnumber ) %]([% item.cardnumber | html %])[% END %]</span>
 [% ELSE %]
 <span class="item-status checkedout">تمت إعارته</span>
 [% END %]
 [% END %]
[% END %]

[% IF NOT ( item.isa('Koha::Item') ) AND item.transfertwhen %] [%# transfertwhen is set in C4::Search, do not have it for course reserves %]
 [% SET itemavailable = 0 %]
 <span class="item-status intransit">في النقل من [% Branches.GetName( item.transfertfrom ) | html %] إلى [% Branches.GetName( item.transfertto ) | html %] منذ [% item.transfertwhen | $KohaDates %]</span>
[% END %]

[% IF NOT( item.isa('Koha::Item') ) AND item.waiting %] [%# Not sure where does come from this waiting flag %]
 [% SET itemavailable = 0 %]
 <span class="item-status onhold">محجوز</span>
[% END %]

[% IF ( item.withdrawn ) %]
 [% SET itemavailable = 0 %]
 [% av_lib_include = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.withdrawn', authorised_value => item.withdrawn, opac => 1 ) %]
 [% IF av_lib_include %]
 <span class="item-status withdrawn">[% av_lib_include | html %]</span>
 [% ELSE %]
 <span class="item-status withdrawn">المادة مسحوبة</span>
 [% END %]
[% END %]


[% IF NOT ( item.isa('Koha::Item') ) AND item.itemnotforloan %]
 [% SET itemavailable = 0 %]
 [% IF ( item.notforloanvalueopac ) %]
 <span class="item-status notforloan">[% item.notforloanvalueopac | html %] [% IF ( item.restrictedvalueopac ) %]<span class="restricted">([% item.restrictedvalueopac | html %])</span>[% END %]</span>
 [% ELSE %]
 <span class="item-status notforloan">لا يعار [% IF ( item.restrictedvalueopac ) %]<span class="restricted">([% item.restrictedvalueopac | html %])</span>[% END %]</span>
 [% END %]
[% ELSIF NOT ( item.isa('Koha::Item') ) AND item.notforloan_per_itemtype %]
 [% SET itemavailable = 0 %]
 <span class="item-status notforloan">لا يعار [% IF ( item.restrictedvalueopac ) %]<span class="restricted">([% item.restrictedvalueopac | html %])</span>[% END %]</span>
[% END %]

[% IF ( item.damaged ) %]
 [% SET itemavailable = 0 %]
 [% av_lib_include = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.damaged', authorised_value => item.damaged, opac => 1 ) %]
 [% IF av_lib_include %]
 <span class="item-status damaged">[% av_lib_include | html %]</span>
 [% ELSE %]
 <span class="item-status damaged">المادة تالفة</span>
 [% END %]
[% END %]

[% IF NOT ( item.isa('Koha::Item') ) AND item.on_order %][%# on_order is only set from opac-detail.pl %]
 [% SET itemavailable = 0 %]
 <span class="item-status onorder">في الطلب</span>
[% END %]

[% IF item.has_pending_hold %]
 [% SET itemavailable = 0 %]
 <span class="item-status pendinghold">حجز في الانتظار</span>
[% END %]

[% IF ( itemavailable ) %]
 [% IF NOT item.isa('Koha::Item') %][% SET restrictedvalueopac = item.restrictedvalueopac %][% END %]
 <span class="item-status available">المتاح[% IF restrictedvalueopac %]<span class="restricted">([% restrictedvalueopac | html %])</span>[% END %]</span>
[% END %]
