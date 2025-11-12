[%- BLOCK account_type_description -%]
 <span>
 [%- IF account.credit_type_code -%]
 [%- PROCESS credit_type_description credit_type = account.credit_type -%]
 [%- ELSIF account.debit_type_code -%]
 [%- PROCESS debit_type_description debit_type = account.debit_type -%]
 [%- END -%]
 [%- PROCESS account_status_description account=account -%]
 </span>
[%- END -%] [%- BLOCK debit_type_description -%] [%- SWITCH debit_type.code -%] [%- CASE 'ACCOUNT'          -%]رسم إنشاء الحساب [%- CASE 'ACCOUNT_RENEW'    -%]رسم تجديد الحساب [%- CASE 'LOST'             -%]مادة ضائعة [%- CASE 'MANUAL'           -%]رسم يدوي [%- CASE 'NEW_CARD'         -%]بطاقة جديدة [%- CASE 'OVERDUE'          -%]غرامة [%- CASE 'PROCESSING'       -%]رسم معالجة مادة ضائعة [%- CASE 'RENT'             -%]رسم الإيجار [%- CASE 'RENT_DAILY'       -%]رسم الإيجار اليومي [%- CASE 'RENT_RENEW'       -%]تجديد مادة إيجار [%- CASE 'RENT_DAILY_RENEW' -%]تجديد مادة إيجار يومي [%- CASE 'RESERVE'          -%]رسم الحجز [%- CASE 'RESERVE_EXPIRED'  -%]الحجز في الانتظار لمد طويلة [%- CASE 'Payout'           -%]دفع [%- CASE                    -%][% debit_type.description | html %] [%- END -%] [%- END -%] [%- BLOCK credit_type_description -%] [%- SWITCH credit_type.code -%] [%- CASE 'PAYMENT'      -%]مدفوعات [%- CASE 'WRITEOFF'     -%]شطب [%- CASE 'FORGIVEN'     -%]معفي [%- CASE 'CREDIT'       -%]ائتمان [%- CASE 'LOST_FOUND'   -%]استرداد رسم مادة ضائعة [%- CASE 'OVERPAYMENT'  -%]استرداد مبلغ زائد مدفوع [%- CASE 'REFUND'       -%]استرداد أموال [%- CASE 'CANCELLATION' -%]رسم ملغي [%- CASE                -%][% credit_type.description | html %] [%- END -%] [%- END -%] [%- BLOCK account_status_description -%] [%- SWITCH account.status -%] [%- CASE 'UNRETURNED' -%]<span> (متراكم)</span>
 [%- CASE 'RETURNED'   -%]<span> (تمت إعادته)</span>
 [%- CASE 'REPLACED'   -%]<span> (تم استبداله)</span>
 [%- CASE 'REFUNDED'   -%]<span> (تم رد المبلغ)</span>
 [%- CASE 'FORGIVEN'   -%]<span> (معفو عنه)</span>
 [%- CASE 'VOID'       -%]<span> (لاغ)</span>
 [%- CASE 'LOST'       -%]<span> (مفقودة)</span>
 [%- CASE 'CANCELLED'  -%]<span> (ملغي)</span>
 [%- CASE              -%]
 [%- END -%]
[%- END -%]

[%- BLOCK offset_type_description -%]
 [%- SWITCH account_offset.type -%]
 [%- CASE 'Credit Applied' -%]<span>تم تطبيق الائتمان</span>
 [%- CASE 'Payment'        -%]<span>الدفع</span>
 [%- CASE 'Manual Credit'  -%]<span>اعتماد يدوي</span>
 [%- CASE 'Manual Debit'   -%]<span>فاتورة يدوية</span>
 [%- CASE 'Lost Item'      -%]<span>تمت إعادة مادة مفقودة</span>
 [%- CASE 'Writeoff'       -%]<span>شطب</span>
 [%- CASE 'Void Payment'   -%]<span>دفع لاغ</span>
 [%- CASE 'CANCELLATION'   -%]<span>رسم ملغي</span>
 [%- CASE                  -%][% account_offset.type | html %]
 [%- END -%]
[%- END -%]
