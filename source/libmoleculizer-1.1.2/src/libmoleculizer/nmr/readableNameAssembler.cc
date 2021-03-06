//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//        This file is part of Libmoleculizer
//
//        Copyright (C) 2001-2009 The Molecular Sciences Institute.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Moleculizer is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// Moleculizer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Moleculizer; if not, write to the Free Software Foundation
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307,  USA
//
// END HEADER
//
// Original Author:
//   Nathan Addy, Scientific Programmer, Molecular Sciences Institute, 2001
//
// Modifing Authors:
//
//

#include "readableNameAssembler.hh"
#include "utl/utility.hh"

#include <vector>

namespace nmr
{
    
    std::string
    readableNameAssembler::createNameFromOutputState( ComplexOutputStateCref aCOS ) const
    {
        // We would like the output to be something like the following.
        // X(phosphorylated):Y:Z(not_phos).
        
        std::string name( "" );
        
        for ( unsigned int molNdx = 0;
              molNdx != aCOS.theMolTokens.size();
              ++molNdx )
        {
            name += aCOS.theMolTokens[molNdx];
            
            std::string modSitesString( "" );
            int numberModSites = 0;
            std::string molNdxAsString = utl::stringify( molNdx );
            
            for ( unsigned int modNdx = 0 ;
                  modNdx!= aCOS.theModificationTokens.size();
                  ++modNdx )
            {
                if ( aCOS.theModificationTokens[modNdx].first == molNdxAsString )
                {
                    modSitesString += aCOS.theModificationTokens[modNdx].second.second;
                    modSitesString += ",";
                    numberModSites++;
                }
            }
            
            if ( numberModSites )
            {
                modSitesString = modSitesString.substr( 0, modSitesString.length() - 1 );
                modSitesString = "(" + modSitesString + ")";
                name += modSitesString;
            }
            name += "-";
        }
        
        name = name.substr( 0, name.length() - 1 );
        
        return name;
    }
    
    
}
