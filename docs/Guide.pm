__END__

=head1 NAME

Guide To Irssi Scripting.

=head1 DESCRIPTION

=head1 LOADING AND UNLOADING SCRIPTS

=head2 File Locations

=head2 Testing

=head2 Loading

Scripts are loaded via C</SCRIPT LOAD I<filename>>.  A default Irssi
configuration also provides the C</RUN> alias as an alternative to C</SCRIPT
LOAD>.


=head2 Unloading

A script can be unloaded via the C</SCRIPT UNLOAD I<name>> command.  The name is
typically the script filename without the F<.pl> extension, so F<nickcolor.pl>
becomes C</SCRIPT UNLOAD nickcolor>.

As part of the unloading process, if the script contains a

    sub UNLOAD {
        ...
    }

function, it will be run just before the script is unloaded and all variables
destroyed. This can be used to clean up any temporary files, shut down any
network connections or processes, and restore any Irssi modifications made.

=head1 ANATOMY OF A SCRIPT

In this section, we develop a very simplistic script and look at the
necessary code.

=head2 Preamble

=head1 COMMONLY SCRIPTED TASKS

=head2 Modifying an input line before sending

=head2 Responding to a public message

=head2 Responding to a private message

=head1 USEFUL THINGS

=head2 Sharing Code Between Scripts

There are 2 main ways for scripts to communicate, either via emitting and
handling Irssi signals, or by calling functions from one another directly.

=head3 Using Signals

=head3 Using Functions

=head2 If In Doubt, Dump!

C<Data::Dumper> is an extremely good way to inspect Irssi internals if you're
looking for an undocumented feature.

The C<DUMP> alias by L<Wouter
Coekaerts|http://wouter.coekaerts.be/site/irssi/aliases> provides an easy way to
check object fields.

Dump perl object (e.g. C</dump Irssi::active_win>):

    /alias DUMP script exec use Data::Dumper\; print Data::Dumper->new([\\$0-])->Dump

=head2 Making Scripts Act Native

An important part of creating a good script is to make it behave as though it
were a part of Irssi. Adhering to some of the standard conventions can make this
easier.

=head3 Provide Help

Scripts commonly store information about how to use them in comments at the top
of their file.  Whilst better than no documentation at all, a preferable approach
is to allow that help to be accessed from within Irssi itself, using the C</HELP>
command.

B<TODO: how>


=head3 Use Tab Completion

One of the great features of Irssi is the ability to complete commands,
subcommands and even certain arguments.

=head3 Use Settings for Customisation

B<TODO: why?>

B<TODO: different types of settings>

B<TODO: register/set/get>

=head3 Use Subcommands to Group Script Functionality

A common theme in Irssi scripts is to define commands with a prefix, such as
C</myscript_foo>, C<myscript_bar>, etc.  This helps to avoid accidentally clobbering
native commands and those defined by other scripts, but is a problem better solved
with I<subcommands>.

Subcommands allow you to bind commands such as C</myscript foo> and C</myscript bar>.
Completions are automatically handled for both the primary command, and any
subcommands contained within it.

The following example demonstrates how to use subcommands from within a script:

    Irssi::command_bind("foo bar", \&subcmd_bar);
    Irssi::command_bind("foo", \&subcmd_handler);

    sub subcmd_handler {
        my ($data, $server, $item) = @_;
        $data =~ s/\s+$//g;
        Irssi::command_runsub('foo', $data, $server, $item);
    }

    sub subcmd_bar {
        my ($args) = @_;
        print "subcommand called with: $args";
    }

=head1 OTHER RESOURCES

The documentation assembled here and elsewhere on this site has been drawn from
many different places, and a lot of valuable information is available from the
following sites.


=over

=item L<http://irssi.org/documentation/perl>

=item L<http://irssi.org/documentation/signals>

=item L<http://irssi.org/documentation/special_vars>

=item L<http://irssi.org/documentation/formats>

=item L<http://irssi.org/documentation/settings>

=item L<http://juerd.nl/site.plp/irssiscripttut>

=item L<http://irchelp.org/irchelp/rfc/rfc.html>

=item L<http://wouter.coekaerts.be/site/irssi/irssi>

=back
