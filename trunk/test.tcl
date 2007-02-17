
load "./bttcl.so"

set get_name 1

if {$get_name} {
   set l [bluetooth::scan -name]
} else {
   set l [bluetooth::scan]
}

foreach el $l {

   set bt_mac [lindex $el 0]
   
   if {$get_name} {
      set bt_name [lindex $el 1]
      puts "mac: $bt_mac, name: $bt_name"
   } else {
      puts "mac: $bt_mac"
   }
}
