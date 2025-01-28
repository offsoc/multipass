/*
 * Copyright (C) Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "enable_zones.h"

#include "animated_spinner.h"
#include "common_callbacks.h"
#include "common_cli.h"
#include "multipass/cli/argparser.h"
#include "multipass/cli/client_common.h"

#include <QCommandLineOption>

namespace multipass::cmd
{
ReturnCode EnableZones::run(ArgParser* parser)
{
    if (const auto ret = parse_args(parser); ret != ParseCode::Ok)
        return parser->returnCodeFrom(ret);

    AnimatedSpinner spinner{cout};
    spinner.start(format("Enabling {}", fmt::join(zone_names, ", ")));

    const auto on_failure = [this, &spinner](const grpc::Status& status) {
        spinner.stop();
        return standard_failure_handler_for(name(), cerr, status);
    };

    ZonesStateRequest request{};
    for (const auto& zone_name : zone_names) request.add_zones(zone_name);
    request.set_available(true);
    request.set_verbosity_level(parser->verbosityLevel());
    return dispatch(
        &RpcMethod::zones_state,
        request,
        [](const ZonesStateReply&) { return Ok; },
        on_failure,
        make_logging_spinner_callback<ZonesStateRequest, ZonesStateReply>(spinner, cerr));
}

std::string EnableZones::name() const
{
    return "enable-zones";
}

QString EnableZones::short_help() const
{
    return QStringLiteral("Make zones available");
}

QString EnableZones::description() const
{
    return QStringLiteral("Makes the requests availability zones available.");
}

ParseCode EnableZones::parse_args(ArgParser* parser)
{
    parser->addPositionalArgument("zone", "Name of the zones to make available", "<zone> [<zone> ...]");

    if (const auto status = parser->commandParse(this); status != ParseCode::Ok)
        return status;

    for (const auto& zone_name : parser->positionalArguments())
        zone_names.push_back(zone_name.toStdString());

    return ParseCode::Ok;
}
} // namespace multipass::cmd
